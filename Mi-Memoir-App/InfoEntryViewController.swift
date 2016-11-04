//
//  InfoEntryViewController.swift
//  Mi-Memoir-App
//
//  Created by K on 11/4/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation
import UIKit

class InfoEntryViewController: UIViewController {
    
    @IBOutlet weak var firstNameTxtField: UITextField!
    @IBOutlet weak var lastNameTxtField: UITextField!
    @IBOutlet weak var emailTxtField: UITextField!
    @IBOutlet weak var phoneTxtField: UITextField!
    @IBOutlet weak var submitButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    
        submitButton.layer.cornerRadius = 15
    }
    
    func sendingImagesAndPersonInfo() {
        
        var parameters = [
            "apiKey" : "API_KEY",
            "affId" : "AFFILIATE_ID",
            "transaction" : "photoCheckoutv2",
            "expiryTime" : "EXPIRATION_TIME",
            "act":"mweb5UrlV2",
            "view":"mweb5UrlV2JSON",
            "devinf":"iPhone,6.1",
            "appver":"3.1",
            "lat":"42.165526",
            "lng":"-87.847672",
            "callBackLink":"http://localhost/callback" ,
            "channelInfo":"web",
            "publisherId":"PUBLISHER_ID",
            "prodGroupId":"Product Group ID specifies the type of photo product on the landing page",
            "affNotes":"If additional notes need to be sent",
            "images": [
                "Array of Image URL's",
                "..."
            ],
            "customer": [
                "firstName":"John",
                "lastName":"Smith",
                "email":"api@test.com",
                "phone":"5555555555",
            ]
        ] as [String : Any]
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}
