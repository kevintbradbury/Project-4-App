//
//  Strings+.swift
//  Mi-Memoir-App
//
//  Created by K on 10/31/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation

extension String {
    func sha1() -> String? {
        
        guard let data = self.data(using: String.Encoding.utf8) else { return nil }
        
        var digest = [UInt8](repeating: 0, count: Int(CC_SHA1_DIGEST_LENGTH))
        
        data.withUnsafeBytes {
            _ = CC_SHA1($0, CC_LONG(data.count), &digest)
        }
        
        let hexBytes = digest.map { String(format: "%02hhx", $0) }
        
        return hexBytes.joined()
    }
}

