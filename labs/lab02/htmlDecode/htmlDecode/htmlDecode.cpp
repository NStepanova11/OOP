#include "stdafx.h"
#include <list>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using map = list<pair<string, string>>;

const map entities = {{
	{ "&", "&amp;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
}};

void DecodeHtml(string &htmlString);
void Replace(string &htmlString, string searchString, string replaceString);

int main()
{
	string htmlString;
	while (getline(cin, htmlString) && (htmlString!=""))
	{
		DecodeHtml(htmlString);
	}
    return 0;
}

void DecodeHtml(string &htmlString)
{
	for (auto element: entities)
	{
		Replace(htmlString, element.first, element.second);
	}
	cout << htmlString << endl;
}

void Replace(string &htmlString, string searchString, string replaceString)
{
	size_t beginPos = 0, findPos = 0;
	do
	{
		findPos = htmlString.find(searchString, beginPos);
		if (findPos!= htmlString.npos)
			htmlString.replace(findPos, searchString.size(), replaceString);
	    beginPos= findPos +replaceString.size();
	} while ((findPos != htmlString.npos) && (beginPos<=htmlString.size()));
}