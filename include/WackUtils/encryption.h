#pragma once

#include <string>
#include <cryptopp/rsa.h>

namespace WackUtils::encryption {
	namespace RSA {
		struct keypair {
			CryptoPP::PublicKey &publicKey;
			CryptoPP::PrivateKey &privateKey;
		};

		struct keypairStr {
			std::string publicKey;
			std::string privateKey;
		};

		/// Generates a public and private key pair.
		/// @param keySize The size of the key to generate (defaulted at 2048).
		/// @returns A key pair containing the public and private keys.
		keypair generateKeyPair(int keySize = 2048);

		/// Encrypts a string using a public key.
		/// @param publicKey The public key to use.
		/// @param plaintext The string to encrypt.
		/// @returns The encrypted string.
		std::string encrypt(const std::string& message, const CryptoPP::PublicKey &publicKey);

		/// Decrypts a string using a private key.
		/// @param privateKey The private key to use.
		/// @param ciphertext The string to decrypt.
		/// @returns The decrypted string.
		std::string decrypt(const std::string& message, const CryptoPP::PrivateKey &privateKey);

		/// Converts a keypair to 2 strings.
		/// @param keypair The keypair to convert.
		/// @returns A pair of strings, containing the public and private keys.
		keypair stringify(CryptoPP::RSA &keypair);
	}
	namespace AES {
		/// Encrypts a string using a key.
		/// @param key The key to use.
		/// @param plaintext The string to encrypt.
		/// @param keySize The size of the key to use (defaulted at 512).
		/// @returns The encrypted string.
		std::string encrypt(const std::string& message, const std::string& key, int keySize = 512);

		/// Decrypts a string using a key.
		/// @param key The key to use.
		/// @param ciphertext The string to decrypt.
		/// @param keySize The size of the key to use (defaulted at 512).
		/// @returns The decrypted string.
		std::string decrypt(const std::string& message, const std::string& key, int keySize = 512);
	}
}