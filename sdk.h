#ifndef __SDK__H
#define	__SDK__H

#include <minwindef.h>
#include <stdio.h>

#define ANY_SIZE 1

#pragma pack(push, 1)
struct WriteDifference
{
	ULONGLONG uOffset;
	BYTE cbCount;
};
#pragma pack(pop)

struct PatchEntryList
{
	struct PatchEntryList* pNext;
	struct WriteDifference Diff;
	BYTE PatchBytes[ANY_SIZE];
};

/*
Purpose: Frees the PathEntryList linked list.

pList - A pointer to a PathEntryList head
*/
VOID FreePatchEntryList(IN struct PatchEntryList* pList);

/*
Purpose: Counts how many entries are in the linked list.
Return: The linked list entry count.

pList - A pointer to a PathEntryList head
*/
DWORD CountPatchEntryList(IN const struct PatchEntryList* pList);

/*
Purpose: Writes a visual representation of the linked list to the specified stream.

pList - A pointer to a PathEntryList head
pStream - A pointer to the FILE struct for writing. (It must have write perms) 
*/
VOID VisualizePatchEntryList(IN const struct PatchEntryList* pList, IN FILE* pStream);

/*
Purpose: Enumerates all the patches in the specified ppf file and outputs a linked list
Return: The function status; Zero if the function succeeded else it failed

lpFile - A pointer to the start of the mapped ppf file
dwFileSize - The ppf file size in bytes
ppList - A pointer to a uninitalized PathEntryList pointer
*/
BOOL EnumPatchInfo(IN LPVOID lpFile, IN DWORD dwFileSize, OUT struct PatchEntryList** ppList);

/*
Purpose: Maps the specified ppf file in memory
Return: The function status; Zero if the function succeeded else it failed

szFile - A pointer to a unicode string that contains the file path
lppFile - A pointer to a void pointer to store the address of the mapped ppf file
lpdwFileSize - A pointer to a dword to store the ppf file size in bytes
*/
BOOL LoadPPFFile(IN LPCWSTR szFile, OUT LPVOID* lppFile, OUT LPDWORD lpdwFileSize);
#endif // !__SDK__H