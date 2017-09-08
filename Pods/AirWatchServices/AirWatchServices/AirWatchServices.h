//
//  AirWatchServices.h
//  AirWatchServices
//
//  Copyright © 2016 VMware, Inc. All rights reserved. This product is protected
//  by copyright and intellectual property laws in the United States and other
//  countries as well as by international treaties. VMware products are covered
//  by one or more patents listed at http://www.vmware.com/go/patents.
//

#import <UIKit/UIKit.h>

//! Project version number for AirWatchServices.
FOUNDATION_EXPORT double AirWatchServicesVersionNumber;

//! Project version string for AirWatchServices.
FOUNDATION_EXPORT const unsigned char AirWatchServicesVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <AirWatchServices/PublicHeader.h>

FOUNDATION_EXPORT NSString* awBytesFromData(NSData *data);
FOUNDATION_EXPORT BOOL awIsCompromised();

