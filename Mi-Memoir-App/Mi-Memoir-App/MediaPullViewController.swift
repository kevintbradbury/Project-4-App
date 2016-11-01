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




class MediaPullerView: UIViewController, UICollectionViewDelegate, UICollectionViewDataSource, UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    
    
    @IBOutlet weak var addPhoto: UIButton!
    @IBOutlet weak var collectionView: UICollectionView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let cancelButton = UIBarButtonItem(title: "Cancel", style: UIBarButtonItemStyle.plain, target: self, action: #selector(MediaPullerView.cancelPicker))
        let doneButton = UIBarButtonItem(title: "Done", style: UIBarButtonItemStyle.plain, target: self, action: #selector(MediaPullerView.donePicker))
        
        navigationItem.setLeftBarButton(cancelButton, animated: true)
        navigationItem.setRightBarButton(doneButton, animated: true)
        
        getSecretKeyRequest()
        collectionView.reloadData()
        
    }
    
    var uploadFileURL: URL?
    var isUploading: Bool = false
    var cellImage: [UIImage] = []
    var tempIndex : Int = 0
    var tempImage: UIImage?;
    
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
            
        }
        dataTask.resume()
        return true
    }
    
    @IBAction func addPhotoAction(_ sender: Any) {
        
        let picker = UIImagePickerController()
        
        picker.delegate = self
        picker.sourceType = .photoLibrary
        
        present(picker, animated: true, completion: nil)
        
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        
        let picker = UIImagePickerController()
        picker.delegate = self
        
        guard let image = info[UIImagePickerControllerOriginalImage] as? String else {return}
        
        if image == kUTTypeImage as String {
            
            var originalImage = info[UIImagePickerControllerOriginalImage] as! UIImage
            var editedImage = info[UIImagePickerControllerEditedImage] as! UIImage?
            var imageToUse = editedImage != nil ? editedImage : originalImage
            
            cellImage.append(imageToUse!)
            print("contents of cellImage are: \(cellImage)")
            
            dismiss(animated: true, completion: nil)
        } else {
            dismiss(animated: true, completion: {})
        }
        
    }
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        
        return cellImage.count
    }
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: "Cell", for: indexPath) as! CollectionViewCell
        
        if indexPath.row == cellImage.count {
            cell.imageView.image = nil;
        }else{
            cell.imageView.image = cellImage[indexPath.row] as UIImage
        }
        
        
        return cell
    }
    
    private let mainOperation = OperationQueue.main
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}

fileprivate let itemsPerRow: CGFloat = 2

fileprivate let sectionInsets = UIEdgeInsets(top: 100.0, left: 40.0, bottom: 100.0, right: 40.0)

extension MediaPullerView: UICollectionViewDelegateFlowLayout {
    
    //1
    func collectionView(_ collectionView: UICollectionView,
                        layout collectionViewLayout: UICollectionViewLayout,
                        sizeForItemAt indexPath: IndexPath) -> CGSize {
        //2
        
        let paddingSpace = sectionInsets.left * (itemsPerRow + 1)
        let availableWidth = view.frame.width - paddingSpace
        let widthPerItem = availableWidth /   itemsPerRow
        
        return CGSize(width: widthPerItem, height: widthPerItem)
    }
    
    //3
    func collectionView(_ collectionView: UICollectionView,
                        layout collectionViewLayout: UICollectionViewLayout,
                        insetForSectionAt section: Int) -> UIEdgeInsets {
        return sectionInsets
    }
    
    // 4
    func collectionView(_ collectionView: UICollectionView,
                        layout collectionViewLayout: UICollectionViewLayout,
                        minimumLineSpacingForSectionAt section: Int) -> CGFloat {
        return sectionInsets.left
    }
    
    func donePicker () {
        if isUploading {return}
        
        cellImage.removeAll()
        
        /*        if loadingNotification == nil {
         loadingNotification = MBProgressHUD.showHUDAddedTo(self.view, animated: true)
         loadingNotification!.mode = MBProgressHUDModeIndeterminate
         }*/
        doUpload()
    }
    
    func cancelPicker () {
        if isUploading {return}
        cellImage.removeAll()
        
    }
    
    func doUpload () {
        
        isUploading = true
        
        //        loadingNotification!.labelText = "Uploading \(tempIndex+1) of \(loadedImages.count)"
        
        let date = Date()
        let timestamp = NSInteger(date.timeIntervalSince1970)
        let S3UploadKeyName = String(timestamp)
        
        print(S3UploadKeyName)
        
        //Create a test file in the temporary directory
        self.uploadFileURL = URL(fileURLWithPath: NSTemporaryDirectory() + S3UploadKeyName)
        print(self.uploadFileURL)
        
        tempImage = cellImage[tempIndex]
        let data = UIImageJPEGRepresentation(tempImage!, 0.5)
        
        var error: NSError? = nil
        if FileManager.default.fileExists(atPath: self.uploadFileURL!.path) {
            //FileManager.default.removeItemAtPath(self.uploadFileURL!.path!, error: &error)
        }
        
        //data.writeToURL(self.uploadFileURL!, atomically: true)
        
        /*        let uploadRequest1 : AWSS3TransferManagerUploadRequest = AWSS3TransferManagerUploadRequest()
         let transferManager = AWSS3TransferManager.defaultS3TransferManager()
         
         uploadRequest1.bucket = S3BucketName
         uploadRequest1.key =  "Uploads/" + S3UploadKeyName
         uploadRequest1.body = self.uploadFileURL
         uploadRequest1.ACL = AWSS3ObjectCannedACL.PublicRead
         
         let task = transferManager.upload(uploadRequest1)
         
         task.continueWithBlock { (task) -> AnyObject! in
         
         self.isuploading = false
         
         if task.error != nil {
         println("Error: \(task.error)")
         self.loadedImages.removeAll()
         //                MBProgressHUD.hideAllHUDsForView(self.view, animated: false)
         
         self.delegate?.cancelPicking(self)
         } else {
         ++self.tempIndex
         var url = "--your url - \(S3UploadKeyName)"
         self.loadedUrls.append(url)
         
         if self.tempIndex == self.loadedImages.count {
         //                    MBProgressHUD.hideAllHUDsForView(self.view, animated: false)
         //                    self.loadingNotification = nil
         
         self.loadedImages.removeAll()
         println("Upload successful")
         self.delegate?.donePicking(self, didPickedUrls: self.loadedUrls)
         } else {
         println("Moving to next upload")
         self.doUpload()
         }
         
         }
         return nil
         }
         
         */
        //remove this code when you activate above commented code
        //self.delegate?.donePicking(self, didPickedUrls: self.loadedUrls)
        
    }
    
}

protocol LimCameraImagePickerDelegate: class {
    func donePicking(_ picker: MediaPullerView, didPickedUrls: [String])
    func cancelPicking(_ picker: MediaPullerView)
}






