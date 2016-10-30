//
//  MediaPullViewController.swift
//  Mi-Memoir-App
//
//  Created by K on 10/25/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation
import UIKit



class MediaPullerView: UIViewController {
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    
    func getSecretKeyRequest() {
        
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
        
//        request.setValue(parameters, forHTTPHeaderField: "Authorization")
        
        var error: JSONSerialization.WritingOptions
        
        let session = URLSession.shared
        
        request.httpMethod = "POST"
        request.httpBody = try? JSONSerialization.data(withJSONObject: parameters, options: [])
        request.addValue("application/json", forHTTPHeaderField: "Content-Type")
        request.addValue("application/json", forHTTPHeaderField: "Accept")
        
        let dataTask = session.dataTask(with: request) {(data, response, error) -> Void in
            
            guard let unwrappedData = data else { return }
            
            guard let jsonDictionary = (try? JSONSerialization.jsonObject(with: unwrappedData, options: [])) as? NSDictionary else { return }
            
            guard let array = (jsonDictionary["return"]) as? NSArray else { return }
            
            for i in array {
                
                guard let dictionary = i as? NSDictionary else { continue }
                
                print(dictionary)
                
                guard let secretKeyDictionary = SecretKeyRequest.fromjson(dictionary: dictionary) else {
                    print("error in guard")
                    return }
                
                //guard let unwrapJSON = try? Data(contentsOf: secretKeyDictionary.accessKeyId) else {return}
                
                secretKeyReqstDictionary.append(secretKeyDictionary)
                
            }
            
        }
        
        dataTask.resume()
        
    }
    
    
    private let mainOperation = OperationQueue.main
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }

}










