#include <WackUtils/encryption.h>

#include <cryptopp/rsa.h>
#include <cryptopp/rng.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>

using namespace WackUtils::encryption;
CryptoPP::DefaultAutoSeededRNG rng = CryptoPP::DefaultAutoSeededRNG();

RSA::keypair RSA::generateKeyPair(int keySize) {
	CryptoPP::InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, keySize);
	CryptoPP::RSA::PrivateKey privateKey(params);
	CryptoPP::RSA::PublicKey publicKey(params);
	return { publicKey, privateKey };
}

std::string RSA::encrypt(const std::string &message, const CryptoPP::PublicKey &key) {
	CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(key);
	std::string encrypted;
	CryptoPP::StringSource(message, true,
		new CryptoPP::PK_EncryptorFilter(rng, encryptor,
			new CryptoPP::StringSink(encrypted)
		)
	);
	return encrypted;
}

std::string RSA::decrypt(const std::string &message, const CryptoPP::PrivateKey &privateKey) {
	CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
	std::string decrypted;
	CryptoPP::StringSource(message, true,
		new CryptoPP::PK_DecryptorFilter(rng, decryptor,
			new CryptoPP::StringSink(decrypted)
		)
	);
	return decrypted;
}

std::string AES::encrypt(const std::string &message, const std::string &key, int keySize) {
	return "";
}

std::string AES::decrypt(const std::string &message, const std::string &key, int keySize) {
	return "";
}
