#ifndef DATABASE_H
#define DATABASE_H

#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "..\Models\IEntity.h"
#include "..\Models\Enum.h"
#include "..\Models\Entity.h"
#include "..\Models\Enemy.h"
#include "..\Models\Player.h"

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::ifstream;
using std::copy;
using std::istream_iterator;
using std::ostream_iterator;

using namespace MT::Project::Models;

namespace MT
{
	namespace Project
	{
		namespace Database
		{
			template <const unsigned int size = 3>
			class Context
			{
			private:
				vector<vector<Enemy>> matrix;
				pair<unsigned int, unsigned int> coords;
				const string ContextFilePath = "Context.xd";
			public:
				Context()
				{
					if (size <= 1) { assert(!"Wrong size of Database"); }
					cout << "Constructor Context" << endl;

					matrix.resize(size);
					for (int i = 0; i < size; i++)
						matrix[i].resize(size);
				}

				void ViewContext()
				{
					for (coords.first = 0; coords.first < Size(); coords.first++)
						for (coords.second = 0; coords.second < Size(); coords.second++)
						{
							for (int i = 0; i < 4; i++)
							{
								cout << coords
									<< " on " << ToString(static_cast<EnemiesValues>(i))
									<< " = " << Get(coords, i) << endl;
							}
						}
					cout << endl;
				}

				void Set(const pair <unsigned int, unsigned int>& coords, unsigned int index, int value)
				{
					matrix[coords.first][coords.second].Set(index) = value;
				}

				int Get(const pair <unsigned int, unsigned int>& coords, unsigned int index)
				{
					return matrix[coords.first][coords.second].Get(index);
				}

				unsigned int Size()
				{
					return size;
				}

				void LoadFromFile()
				{
					ifstream File;

					File.open(ContextFilePath);

					// Print file content
					/*copy(
						istream_iterator<string>(File),
						istream_iterator<string>(),
						ostream_iterator<string>(cout, " "));*/

					if (File.good())
					{
						for (coords.first = 0; coords.first < Size(); coords.first++)
						{
							for (coords.second = 0; coords.second < Size(); coords.second++)
							{
								int index = -1;

								while (index < 4)
								{
									if (index == -1)
									{
										File >> matrix[coords.first][coords.second].SetName();
									}
									else
									{
										File >> matrix[coords.first][coords.second].Set(index);
									}

									cout << matrix[coords.first][coords.second].ToString() << endl;
									index++;
								}
							}
						}
					}
					else { assert(!"No database file in directory"); }

					File.close();
				}

				~Context()
				{
					cout << "Destructor Context " << endl;
				}
			};
		}
	}
}

#endif