//
//  ViewController.swift
//  Mi-Memoir-App
//
//  Created by K on 10/25/16.
//  Copyright © 2016 K. All rights reserved.
//

import UIKit
import FacebookCore
import FacebookLogin

class ViewController: UIViewController {

    @IBOutlet weak var fbButton: UITextField!
    @IBOutlet weak var button: UIButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    @IBAction func buttonPress(_ sender: AnyObject) {
        LoginButton
        
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

