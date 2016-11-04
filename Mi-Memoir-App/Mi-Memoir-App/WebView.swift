//
//  WebView.swift
//  Mi-Memoir-App
//
//  Created by K on 11/4/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation
import UIKit

class WebView: UIViewController {
    
    @IBOutlet weak var walgreensCheckoutView: UIWebView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    
        var landingURL = "https://m5-qa.walgreens.com/mweb5/checkout/orderprints.jsp?cartId=65764355656"
        
        if let url = NSURL(string: landingURL) {
            UIApplication.shared.open(url as URL, options: [:], completionHandler: nil)
        }
    }
    
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}
