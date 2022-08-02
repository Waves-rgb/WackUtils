#include <WackUtils/encryption.h>
#include <gtest/gtest.h>

TEST(Encryption, RSA_keyPair) {
	auto keyPair = WackUtils::encryption::RSA::generateKeyPair(2048);
	ASSERT_TRUE(keyPair.publicKey.GetModulus().BitCount() == 2048);
	ASSERT_TRUE(keyPair.privateKey.GetModulus().BitCount() == 2048);
}