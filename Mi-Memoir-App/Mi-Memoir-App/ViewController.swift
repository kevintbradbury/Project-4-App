//
//  ViewController.swift
//  Mi-Memoir-App
//
//  Created by K on 10/25/16.
//  Copyright © 2016 K. All rights reserved.
//

import UIKit
import FBSDKCoreKit
import FBSDKLoginKit


@IBDesignable

class ViewController: UIViewController, FBSDKLoginButtonDelegate {
    
    let loginButton: FBSDKLoginButton = {
        let button = FBSDKLoginButton()
        button.readPermissions = ["email"]
        return button
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        view.addSubview(loginButton)
        loginButton.center = view.center
        loginButton.delegate = self
        
        if let token = FBSDKAccessToken.current() {
            fetchProfile()
        }
        
    }
    
    func fetchProfile() {
        print("fetch profile")
        
        let parameters = ["fields": "email, first_name, last_name, picture"]
        FBSDKGraphRequest(graphPath: "me", parameters: parameters).start { (connection, result, error) -> Void in
            
            if error != nil {
                print(error)
                return
            }
            
        }
    }
    
    func loginButton(_ loginButton: FBSDKLoginButton!, didCompleteWith result: FBSDKLoginManagerLoginResult!, error: Error!) {
        
        let manager = FBSDKLoginManager.self()
        
        if error != nil {
            print("Login did not complete due to \(error)")
        }else if (result.isCancelled){
            print("result was cancelled")
        }else {
            
            if result.grantedPermissions.contains("email") {
                
            }
        }
        
        print("completed Login")
        fetchProfile()
    }
    
    func loginButtonDidLogOut(_ loginButton: FBSDKLoginButton!) {
        
    }
    func loginButtonWillLogin(_ loginButton: FBSDKLoginButton!) -> Bool {
        return true
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
}

