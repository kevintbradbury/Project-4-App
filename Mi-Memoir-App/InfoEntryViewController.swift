//
//  InfoEntryViewController.swift
//  Mi-Memoir-App
//
//  Created by K on 11/4/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation
import UIKit
import CoreLocation
import MapKit

class InfoEntryViewController: UIViewController, CLLocationManagerDelegate, MKMapViewDelegate {
    
    @IBOutlet weak var firstNameTxtField: UITextField!
    @IBOutlet weak var lastNameTxtField: UITextField!
    @IBOutlet weak var emailTxtField: UITextField!
    @IBOutlet weak var phoneTxtField: UITextField!
    @IBOutlet weak var submitButton: UIButton!
    @IBAction func submitAction(_ sender: Any) {
        
        var landingURL = "https://m5-qa.walgreens.com/mweb5/checkout/orderprints.jsp?cartId=65764355656"
        
        if let url = NSURL(string: landingURL) {
            UIApplication.shared.open(url as URL, options: [:], completionHandler: nil)
        }
    
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        locationManager = CLLocationManager()
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.distanceFilter = kCLDistanceFilterNone
        locationManager.requestWhenInUseAuthorization()
        locationManager.startUpdatingLocation()
        
        submitButton.layer.cornerRadius = 15
        
        
    }
    
    var locationManager: CLLocationManager!
    var location: CLLocation?

    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let userLocation: CLLocation = locations [0]
        location = userLocation
        let latitude = userLocation.coordinate.latitude
        let longitude = userLocation.coordinate.longitude
        
        print("CLLocation is - Latitude : \(latitude) and Logitude : \(longitude) ")
        
    }
    
    
    func sendingImagesAndPersonInfo() {
        
        guard var firstName = firstNameTxtField.text else {return}
        guard var lastName = lastNameTxtField.text else {return}
        guard var email = emailTxtField.text else {return}
        guard var phone = phoneTxtField.text else {return}
        
        var parameters = [
            "apiKey" : "API_KEY",
            "affId" : "AFFILIATE_ID",
            "transaction" : "photoCheckoutv2",
            "expiryTime" : "EXPIRATION_TIME",
            "act":"mweb5UrlV2",
            "view":"mweb5UrlV2JSON",
            "devinf":"iPhone,6.1",
            "appver":"3.1",
            "lat": location!.coordinate.latitude,
            "lng": location!.coordinate.longitude,
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
                "firstName": firstName,
                "lastName": lastName,
                "email": email,
                "phone": phone,
            ]
            ] as [String : Any]
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}
