/***************************************************************************************************************************************************************************************************************************
																																																						   *
This file is part of CertiVox M-Pin Client and Server Libraries.																																						   *
The CertiVox M-Pin Client and Server Libraries provide developers with an extensive and efficient set of strong authentication and cryptographic functions.																   *
For further information about its features and functionalities please refer to http://www.certivox.com																													   *
The CertiVox M-Pin Client and Server Libraries are free software: you can redistribute it and/or modify it under the terms of the BSD 3-Clause License http://opensource.org/licenses/BSD-3-Clause as stated below.		   *
The CertiVox M-Pin Client and Server Libraries are distributed in the hope that they will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   *
Note that CertiVox Ltd issues a patent grant for use of this software under specific terms and conditions, which you can find here: http://certivox.com/about-certivox/patents/											   * 	
Copyright (c) 2013, CertiVox UK Ltd																																														   *	
All rights reserved.																																																	   *
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:																			   *
�	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.																						   *	
�	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.			   *	
�	Neither the name of CertiVox UK Ltd nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.								   *
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,																		   *
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS																	   *
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE																	   *	
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,														   *
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.																		   *	
																																																						   *
***************************************************************************************************************************************************************************************************************************/
/*! \file  CvAesGcm.h
    \brief C++ wrapper for the MIRACL AES GCM functionality

*-  Project     : SkyKey SDK
*-  Authors     : Mony Aladjem
*-  Company     : Certivox
*-  Created     : January 23, 2013, 3:08 PM
*-  Last update : February 15, 2013
*-  Platform    : Windows XP SP3 - Windows 7
*-  Dependency  : MIRACL library

 C++ wrapper for the MIRACK/SkyKeyXT AES GCM functionality.
 The class API is adapted to the existing SkyKey soltuion.

*/

#ifndef CVAESGCM_H
#define	CVAESGCM_H

#include "CvCommon.h"

#include "common_c.h"

extern "C"
{
	#include "miracl.h"
}

#include <string>

#ifdef mr_compare
	#undef mr_compare
#endif

class CvAesGcm
{
public:
	typedef std::string	String;
	
	static const int DEFAULT_IV_LENGTH = 24;
	static const int DEFAULT_HEADER_LENGTH = 16;
	
	CvAesGcm( csprng* apRng = NULL );
	virtual ~CvAesGcm()	{}
	
	bool GenerateKey( OUT String& aKey, int aLen = AS );

	////////////////////////////////////////////////////////////////////
	//	Encrypt
	/// @brief	Encrypt data using AES GSM.
	///
	/// @param	aKey			- Base64-encoded AES key.
	/// @param	aPlainData		- Plain data to be encrypted (might be binary).	
	/// @param	aCipher			- OUT - Resulting Base64-encoded cipher.	
	/// @param	aLengthIV		- Desired Initialization Vector length.	
	/// @param	aLengthHeader	- Desired Header length.
	///
	/// @return	true on success, false otherwise.
	////////////////////////////////////////////////////////////////////
	bool Encrypt( const String& aKey, const String& aPlainData, OUT String& aCipher,
				int aLengthIV = DEFAULT_IV_LENGTH, int aLengthHeader = DEFAULT_HEADER_LENGTH );

	////////////////////////////////////////////////////////////////////
	//	Decrypt
	/// @brief	Decrypt data using AES GSM.
	///
	/// @param	aKey			- Base64-encoded AES key.
	/// @param	aCipher			- Base64-encoded cipher to be decrypted.	
	/// @param	aPlainData		- OUT - Resulting plain data (might be binary).	
	/// @param	aLengthIV		- Initialization Vector length.	
	/// @param	aLengthHeader	- Header length.
	///
	/// @return	true on success, false otherwise.
	////////////////////////////////////////////////////////////////////
	bool Decrypt( const String& aKey, const String& aCipher, OUT String& aPlainData,
				int aLengthIV = DEFAULT_IV_LENGTH, int aLengthHeader = DEFAULT_HEADER_LENGTH );
	
private:
	CvAesGcm(const CvAesGcm& orig)	{}
	
	void RandomiseBuffer( char* apBuffer, int aLength );
	
	csprng*	m_pRng;	// Random Number Generator	
};

#endif	/* CVAESGCM_H */

