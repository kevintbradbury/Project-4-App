//
//  MediaPullViewController.swift
//  Mi-Memoir-App
//
//  Created by K on 10/25/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation
import UIKit
import Photos
import MediaPlayer
import MobileCoreServices
import QuartzCore


class MediaPullerView: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UICollectionViewDataSource, UICollectionViewDelegate {
    
    @IBOutlet weak var addPhotoButton: UIButton!
    @IBOutlet weak var collectionView: UICollectionView!
    @IBAction func addPhotoAction(_ sender: Any) {
        
        let picker = UIImagePickerController()
        
        picker.delegate = self
        picker.sourceType = .photoLibrary
        
        present(picker, animated: true, completion: nil)
        
    }
    @IBOutlet weak var uploadPhotoButton: UIButton!
    @IBAction func uploadPhotoAction(_ sender: Any) {
    
        uploadPhotos()
        
    }
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        getSecretKeyRequest()
        collectionView.reloadData()
        
    }
    
    var uploadFileURL: URL?
    var isUploading: Bool = false
    var cellImage: [UIImage] = []
    var tempIndex : Int = 0
    var tempImage: UIImage?;
    
    // Talk to the web ------------------------
    func getSecretKeyRequest() -> Bool {
        
        let walgreensKeyRequestURL = "https://services-qa.walgreens.com/api/util/mweb5url"
        
        let parameters = ["serviceType":"wagS3",
                          "apiKey":"xIjnSFIkc90LGqIIGeo82Eyj5jOFQ8UQ",
                          "affId":"photoapi",
                          "act":"genCredV2",
                          "view":"genCredV2JSON",
                          "devinf":"iPhone,6.1",
                          "appver":"3.1"]
        
        let url = URL(string: walgreensKeyRequestURL)!
        var request = URLRequest.init(url: url)
        
        var error: JSONSerialization.WritingOptions
        let session = URLSession.shared
        
        request.httpMethod = "POST"
        request.httpBody = try? JSONSerialization.data(withJSONObject: parameters, options: [])
        request.addValue("application/json", forHTTPHeaderField: "Content-Type")
        request.addValue("application/json", forHTTPHeaderField: "Accept")
        
        let dataTask = session.dataTask(with: request) {(data, response, error) -> Void in
            
            guard let unwrappedData = data else { return }
            guard let jsonDictionary = (try? JSONSerialization.jsonObject(with: unwrappedData, options: [])) as? NSDictionary else { return }
            
            guard let secretKeyDictionary = SecretKeyRequest.fromjson(dictionary: jsonDictionary) else {
                print("error in guard")
                return }
            
            secretKeyReqstDictionary = secretKeyDictionary
            
            guard (secretKeyReqstDictionary != nil) else { return }
            print(secretKeyReqstDictionary!)
            
        }
        dataTask.resume()
        return true
    }
    
    func uploadPhotos() -> Bool {
        
        let uploadURL = secretKeyReqstDictionary?.uploadUrl
        
        let sha1EncodedString = secretKeyReqstDictionary?.secretKey.sha1()
        
        let sessionID = secretKeyReqstDictionary?.sessionId
        
        let accessKeyID = secretKeyReqstDictionary?.accessKeyId
        
        let utf8String = "PUT\n" + "\n" + "image/jpg\n" + "Fri, 30 Jan 2015 12:15:45 GMT\n" + "x-amz-security-token: \(sessionID)\n" + "/\(uploadURL)/;\(photoPathsArray[0])"
        
        let hmac = "$signature= hash_hmac('sha1', " + utf8String + "," + sha1EncodedString! + ", true);"
        
        let hmacData = hmac.data(using: String.Encoding.utf8)!
        
        let base64String = hmacData.base64EncodedData(options: [])
        
        let signedEncodedData = "$signedEncodedData = base64_encode(\(base64String));"
        
        // let authorizationfield = "$AuthValue = " + "AWS" + accessKeyID + ":" + signedEncodedData + ";"
        
        let photoUploadParameters = [
            "PUT" : "/myImage_01_30_2015_12154510.jpg HTTP/1.1",
            "Host:" : "\(uploadURL)",
            "Date:" : "Fri, 30 Jan 2015 12:15:45 GMT",
            "Authorization:" : "\(signedEncodedData)",
            "Content-Type:":  "image/jpg",
            "Content-Length:" : "11434",
            "Expect:": "100-continue",
            "x-amz-security-token:" : "\(sessionID)"]
        
        //Image Data
        let imageData = UIImageJPEGRepresentation(cellImage[0], 1)
        let base64ImageString = imageData!.base64EncodedString(options: NSData.Base64EncodingOptions.lineLength64Characters)
        
        //Setting URL
        let url = URL(string: uploadURL!)
        var request = URLRequest.init(url: url!)
        
        var error: JSONSerialization.WritingOptions
        let session = URLSession.shared
        
        request.httpMethod = "POST"
        request.httpBody = try? JSONSerialization.data(withJSONObject: photoUploadParameters, options: [])
        request.addValue("application/json", forHTTPHeaderField: "Content-Type")
        request.addValue("application/json", forHTTPHeaderField: "Accept")
        
        let dataTask = session.dataTask(with: request) {(data, response, error) -> Void in
            
            guard let unwrappedData = data else { return }
            guard let jsonDictionary = (try? JSONSerialization.jsonObject(with: unwrappedData, options: [])) as? NSDictionary else { return }
            
            
        }
        return true
    }
    
    //Get Photos ----------------------------
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        
        guard let image = info[UIImagePickerControllerOriginalImage] as? UIImage else {return}
        
        cellImage.append(image)
        
//        guard let imageString = info[UIImagePickerControllerOriginalImage] as? String else { return }
//        
//        photoPathsArray.append(imageString)
        
        collectionView.reloadData()
//        dismiss(animated: true, completion: nil)
        
    }
    
    var photoPathsArray: [String] = []
    
    let mainOperation = OperationQueue.main
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        
        return cellImage.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "Cell", for: indexPath) as! CollectionViewCell
        
        cell.imageView?.image = self.cellImage[indexPath.row]
        
        return cell
    }
    
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}










