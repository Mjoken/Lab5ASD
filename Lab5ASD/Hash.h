#pragma once
#include <iostream>
class Hash
{
private:
	typedef unsigned short int HashlndexType;
	unsigned char Rand8[256];
	unsigned int HashTableSize;
public:
	struct HashNode
	{
		HashNode() : Collision(nullptr), FIO(nullptr) {
			for (size_t i{}; i < 16; i++) {
				phoneNuber[i] = 0;
			}
		};
		char* FIO;
		char* phoneNuber = new char[16];
		HashNode* Collision;

	};
	HashNode** Table;
	Hash(unsigned int size) : HashTableSize(size) {
		Table = new HashNode* [HashTableSize];
	};
	~Hash() {
		delete[] Table;
	};
	HashlndexType HashFunc(char* str)
	{
		HashlndexType h;
		unsigned char h1, h2;

		if (*str == 0) return 0;

		h1 = *str;
		h2 = *str + 1;
		str++;
		while (*str)
		{
			h1 = Rand8[h1 ^ *str];
			h2 = Rand8[h2 ^ *str];
			str++;
		}
		/* h is in range 0..65535 */
		h = ((HashlndexType)h1 << 8) | (HashlndexType)h2;

		/* use division method to scale */
		return h % HashTableSize;
	}
	HashNode* Collision(HashlndexType hash) {
		if (Table[hash]->FIO != nullptr){
			for (size_t i{hash}; i < HashTableSize; i++) {
				if (Table[i]->FIO == nullptr) { 
					Table[hash]->Collision = Table[i];
					return Table[i];
				}
			}
		}
	}
	void addRecord(char* phoneNuber, char* fio) {
		if (Table[HashFunc(phoneNuber)]->FIO == nullptr) {
			Table[HashFunc(phoneNuber)]->FIO = fio;
			Table[HashFunc(phoneNuber)]->phoneNuber = phoneNuber;
		}
		else {
			HashNode* temp = Collision(HashFunc(phoneNuber));
			temp->FIO = fio;
			temp->phoneNuber = phoneNuber;
		}
		
	}
	HashNode* Find(char* phoneNuber) {
		if (phoneNuber == Table[HashFunc(phoneNuber)]->phoneNuber) {
			return Table[HashFunc(phoneNuber)];
		}
		else {
			return Table[HashFunc(phoneNuber)]->Collision;
		}
	}
		

};
