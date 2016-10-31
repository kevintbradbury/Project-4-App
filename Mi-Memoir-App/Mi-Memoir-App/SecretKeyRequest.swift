//
//  SecretKeyRequest.swift
//  Mi-Memoir-App
//
//  Created by K on 10/29/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation

var secretKeyReqstDictionary: SecretKeyRequest?

struct SecretKeyRequest {
    
    let secretKey: String
    let accessKeyId: String
    let sessionId: String
    let uploadUrl: String
    let err: String
    
    static func fromjson(dictionary: NSDictionary) -> SecretKeyRequest? {
        guard let secretKey = dictionary["secretKey"] as? String,
            let accessKeyId = dictionary["accessKeyId"] as? String,
            let sessionId = dictionary["sessionId"] as? String,
            let uploadUrl = dictionary["uploadUrl"] as? String,
            let err = dictionary["err"] as? String else {
                print("guard failed on SecretKeyRequest Struct")
                return nil
        }
        
        return SecretKeyRequest(secretKey: secretKey, accessKeyId: accessKeyId, sessionId: sessionId, uploadUrl: uploadUrl, err: err)
        
    }
}
