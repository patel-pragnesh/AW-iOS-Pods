//
//  SDKUIBackButton.swift
//  AWPresentation
//
//  Copyright © 2016 VMware, Inc. All rights reserved. This product is protected
//  by copyright and intellectual property laws in the United States and other
//  countries as well as by international treaties. VMware products are covered
//  by one or more patents listed at http://www.vmware.com/go/patents.
//

import UIKit

public class SDKUIBackButton: UIButton {
    public override func awakeFromNib() {
        super.awakeFromNib()
        self.tintColor = UIColor(colorLiteralRed: 73/255.0, green: 73/255.0, blue: 73/255.0, alpha: 1)
        self.alpha = 1;
    }
}
