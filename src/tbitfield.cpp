// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len) //конструктор по умолчанию
{
		if (len <= 0) 
			throw "Incorrect value";
		bitLen = len;
		memLen = (bitLen / (sizeof(uint) * 8)) + 1;
		pMem = new uint[memLen];
		for (int i = 0; i < memLen; i++)
			pMem[i] = 0;
}
// ---------------------------------------------------------------------------
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new uint[memLen];
	for (int i = 0; i < memLen; i++)
		pMem[i] = bf.pMem[i];
}
// ---------------------------------------------------------------------------
TBitField::~TBitField()
{
	delete[]pMem;
	pMem = NULL;
}
// ---------------------------------------------------------------------------
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect value";
	return (n / (sizeof(uint) * 8));
}
// ---------------------------------------------------------------------------
uint TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect value";
	return 1 << (n & (sizeof(uint) * 8 - 1));
}
// ---------------------------------------------------------------------------
// доступ к битам битового поля
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}
// ---------------------------------------------------------------------------
void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect value";
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] | GetMemMask(n);

}
// ---------------------------------------------------------------------------
void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect value";
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & ~GetMemMask(n);
}
// ---------------------------------------------------------------------------
int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= bitLen))
		throw "Incorrect value";
	int i = GetMemIndex(n);
	return (pMem[i] & GetMemMask(n));
}
// ---------------------------------------------------------------------------
// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		bitLen = bf.bitLen;
		memLen = bf.memLen;
		pMem = new uint[memLen];
		for (int i = 0; i < memLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}
// ---------------------------------------------------------------------------
int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (bitLen != bf.bitLen)
		res = 0;
	else
		for (int i = 0; i < memLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
	return res;
}
// ---------------------------------------------------------------------------
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 0;
	if (bitLen != bf.bitLen)
		res = 1;
	else
		for (int i = 0; i < memLen; i++)
			if (pMem[i] != bf.pMem[i]) 
			{
				res = 1;
				break;
			}
	return res;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = bitLen;
	if (bf.bitLen>len)
		len = bf.bitLen;
	TBitField temp(len);
	for (int i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = bitLen;
	if (bf.bitLen>len)
		len = bf.bitLen;
	TBitField temp(len);
	for (int i = 0; i < memLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator~(void) // отрицание
{
	int len = bitLen;
	TBitField temp(len);
	for (int i = 0; i < bitLen; i++)
	{
		if (GetBit(i) == 0)
			temp.SetBit(i);
		else
			temp.ClrBit(i);
	}
	return temp;
}
// ---------------------------------------------------------------------------
// ввод/вывод
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string temp;
	istr >> temp;
	if (temp.size() != bf.GetLength())
		throw "Incorrect value";
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (temp[i] == '0')
			bf.ClrBit(i);
		else if (temp[i] == '1')
			bf.SetBit(i);
		else
			throw "Incorrect value";
	}
	return istr;
}
// ---------------------------------------------------------------------------
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.bitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << 1;
		else
			ostr << 0;
	}
	return ostr;
}