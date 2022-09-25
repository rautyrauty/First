//Given two strings ransomNoteand magazine, return true if ransomNote 
//can be constructed by using the letters from magazine and false otherwise.
//
//Each letter in magazine can only be used once in ransomNote.
#include "Solutions.h"
#include <map>
bool Solutions::canConstruct(std::string ransomNote, std::string magazine)
{
	int magazsize = magazine.size();
	std::map<char, unsigned short int> MagazineMap;
	for (char ch : magazine)
	{
		auto CharIteratorInMap = MagazineMap.find(ch);
		if (CharIteratorInMap == MagazineMap.end())
		{
			MagazineMap.emplace(ch, 1);
			continue;
		}
		++CharIteratorInMap->second;
	}
	for (char ch : ransomNote)
	{
		auto CharIteratorInMap = MagazineMap.find(ch);
		if ((CharIteratorInMap == MagazineMap.end()) or (CharIteratorInMap->second == 0)) return false;
		--CharIteratorInMap->second;
	}
	return true;
}