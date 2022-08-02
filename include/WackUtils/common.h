#pragma once

// ----------------------------------- \\
//              WackUtils              \\
// ----------------------------------- \\
//  A collection of utilities to make  \\
//     life a little easier for me     \\
// ----------------------------------- \\
// Language: C++				       \\
// Last Updated: 8/1/2022			   \\
// Target Platform: Windows     	   \\
// ----------------------------------- \\
// Libraries in use:				   \\
//  - OpenSSL (encryption.h)           \\
//  - CURL    (networking.h)           \\
// ----------------------------------- \\

enum filterReturn_t {
	FILTER_REJECT = 0,
	FILTER_ACCEPT = 1,
	FILTER_STOP   = 2,
	FILTER_ACCEPT_STOP = 3,
};