//
//  ImagePicker.swift
//  Mi-Memoir-App
//
//  Created by K on 11/1/16.
//  Copyright © 2016 K. All rights reserved.
//

import Foundation
import UIKit

class ImagePickerController: UIView {

    var cancelButton = UIBarButtonItem(title: "Cancel", style: UIBarButtonItemStyle.plain, target: self, action: Selector(("cancelPicker")))
    var doneButton = UIBarButtonItem(title: "Done", style: UIBarButtonItemStyle.done, target: self, action: Selector(("donePicker")))

}
