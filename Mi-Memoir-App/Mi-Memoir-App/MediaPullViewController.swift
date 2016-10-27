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
        let printIO = PrintIO(viewController: MediaPullerView(), recipeId: "66119527-67d0-47b0-933f-fabdfc614e4", isInTestMode: true)
    }
    
    var photoSource = MyCustomPhotoSource()
    var setCustomPhotoSources = printIO()
    var photoSource = ()

    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
}

class PIODefaultPhotoSource: PIOPhotoSource {
    
    func requestItems(for item: PIOPhotoSourceItem!, currentScope: PIOPhotoSourceItem!, count: UInt, page: UInt, withCompletionHandler completionHandler: PIOItemsCompletionHandler!, errorHandler: PIOPhotoSourceErrorHandler!) {
        
        title()
        buttonIconPath()
        
        
    }
    
}

class PIODefaultPhotoSourceItem: NSObject, PIOPhotoSourceItem {

    func uniqueIdentifier() -> String! {
        
    }
    func isImageItem() -> Bool {
        
    }
    func fetchImage(in photoSource: PIOPhotoSource!, isThumbnail thumbnail: Bool, withCompletionHandler imageFetchCompletionHandler: ((UIImage?) -> Void)!) {
        
    }
    
}
