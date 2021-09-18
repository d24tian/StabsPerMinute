#include "header.h"

void StartLevel(int index)
{
    ///Clear all objects except for the player
	blocks.clear();
	decorations.clear();

    ///Create blocks
	blockPoint tmpAdd;
    string line = "";
    int paramCounter = 0;
    string currentParam = "";
    int intParam = 0;

	///Open file--------------------------------------------------
	std::string currentLevel = "";
	if (level == 0)
    {
        currentLevel = "levels/0.txt";
    }

    /*
    ofstream writeFile(currentLevel, ios::trunc);

    ///Write file--------------------------------------------------
    ///(THIS IS TEMPORARY, WILL BE DELETED AFTER LEVEL-BUILDING IS COMPLETELY FINISHED)
    if (writeFile.is_open())
    {
        ///Center room--------------------------------------------------
        writeFile << "///Center room" << endl;

        ///Decorations----------
        ///Floor
        for (int i = -16; i <= -11; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }
        for (int i = 11; i <= 16; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        for (int i = -10; i <= 10; i++)
        {
            writeFile << "-1 " << i << " 7 0;" << endl;
        }

        ///Ceiling
        for (int i = -16; i <= -1; i++)
        {
            writeFile << "-1 " << i << " 1 1;" << endl;
        }
        for (int i = 1; i <= 16; i++)
        {
            writeFile << "-1 " << i << " 1 1;" << endl;
        }

        writeFile << "-1 0 2 1;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 8; i <= 12; i++)
        {
            for (int j = -16; j <= 16; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Platforms at the ends of the area
        for (int i = -16; i <= -11; i++)
        {
            writeFile << "0 " << i << " 7 0;" << endl;
        }
        for (int i = 11; i <= 16; i++)
        {
            writeFile << "0 " << i << " 7 0;" << endl;
        }

        ///Ceiling
        for (int i = -16; i <= 16; i++)
        {
            writeFile << "0 " << i << " 0 0;" << endl;
            writeFile << "0 " << i << " 1 0;" << endl;
        }

        ///One block hanging down in middle of screen
        writeFile << "0 0 2 0;" << endl;

        ///Room 1--------------------------------------------------
        writeFile << "///Room 1" << endl;

        ///Decorations----------
        ///Floor
        for (int i = 17; i <= 48; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        ///Ceiling
        for (int i = 17; i <= 47; i++)
        {
            writeFile << "-1 " << i << " 0 1;" << endl;
        }

        ///Floating platform floor
        writeFile << "-1 25 3 0;" << endl;
        writeFile << "-1 26 3 0;" << endl;
        writeFile << "-1 27 2 0;" << endl;
        writeFile << "-1 28 2 0;" << endl;
        writeFile << "-1 29 3 0;" << endl;
        writeFile << "-1 30 3 0;" << endl;
        ///Floating platform ceiling
        for (int i = 25; i <= 30; i++)
        {
            writeFile << "-1 " << i << " 4 1;" << endl;
        }

        ///Pillars under floating platform
        writeFile << "-1 25 5 4;" << endl;
        writeFile << "-1 25 6 3;" << endl;
        writeFile << "-1 30 5 4;" << endl;
        writeFile << "-1 30 6 3;" << endl;

        ///Ceiling piece on blocks coming down at the end
        writeFile << "-1 48 4 1;" << endl;

        ///Pillar at end
        writeFile << "-1 48 5 4;" << endl;
        writeFile << "-1 48 6 3;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 7; i <= 12; i++)
        {
            for (int j = 17; j <= 48; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Ceiling
        for (int i = 17; i <= 48; i++)
        {
            writeFile << "0 " << i << " 0 0;" << endl;
        }

        ///Floating platform
        for (int i = 25; i <= 30; i++)
        {
            writeFile << "0 " << i << " 4 0;" << endl;
        }
        writeFile << "0 27 3 0;" << endl;
        writeFile << "0 28 3 0;" << endl;

        ///Blocks coming down at the end
        for (int i = 1; i <= 4; i++)
        {
            writeFile << "0 48 " << i << " 0;" << endl;
        }

        ///Room -1--------------------------------------------------
        writeFile << "///Room -1" << endl;

        ///Decorations----------
        ///Floor
        for (int i = -17; i >= -48; i--)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        ///Ceiling
        for (int i = -17; i >= -47; i--)
        {
            writeFile << "-1 " << i << " 0 1;" << endl;
        }

        ///Floating platform floor
        writeFile << "-1 -25 3 0;" << endl;
        writeFile << "-1 -26 3 0;" << endl;
        writeFile << "-1 -27 2 0;" << endl;
        writeFile << "-1 -28 2 0;" << endl;
        writeFile << "-1 -29 3 0;" << endl;
        writeFile << "-1 -30 3 0;" << endl;
        ///Floating platform ceiling
        for (int i = -25; i >= -30; i--)
        {
            writeFile << "-1 " << i << " 4 1;" << endl;
        }

        ///Ceiling piece on blocks coming down at the end
        writeFile << "-1 -48 4 1;" << endl;

        ///Pillar at end
        writeFile << "-1 -48 5 4;" << endl;
        writeFile << "-1 -48 6 3;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 7; i <= 12; i++)
        {
            for (int j = -17; j >= -48; j--)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Ceiling
        for (int i = -17; i >= -48; i--)
        {
            writeFile << "0 " << i << " 0 0;" << endl;
        }

        ///Floating platform
        for (int i = -25; i >= -30; i--)
        {
            writeFile << "0 " << i << " 4 0;" << endl;
        }
        writeFile << "0 -27 3 0;" << endl;
        writeFile << "0 -28 3 0;" << endl;

        ///Pillars under floating platform
        writeFile << "-1 -25 5 4;" << endl;
        writeFile << "-1 -25 6 3;" << endl;
        writeFile << "-1 -30 5 4;" << endl;
        writeFile << "-1 -30 6 3;" << endl;

        ///Blocks coming down at the end
        for (int i = 1; i <= 4; i++)
        {
            writeFile << "0 -48 " << i << " 0;" << endl;
        }

        ///Room 2--------------------------------------------------
        writeFile << "///Room 2" << endl;

        ///Decorations----------
        ///Ground platforms
        for (int i = 49; i <= 54; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }
        writeFile << "-1 56 6 0;" << endl;
        writeFile << "-1 57 6 0;" << endl;
        writeFile << "-1 59 6 0;" << endl;
        writeFile << "-1 60 6 0;" << endl;
        for (int i = 62; i <= 64; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }
        for (int i = 69; i <= 80; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        ///Pits
        writeFile << "-1 55 9 0;" << endl;
        writeFile << "-1 58 9 0;" << endl;
        writeFile << "-1 61 9 0;" << endl;
        for (int i = 65; i <= 68; i++)
        {
            writeFile << "-1 " << i << " 9 0;" << endl;
        }

        ///Ceiling
        for (int i = 50; i <= 55; i++)
        {
            writeFile << "-1 " << i << " 0 1;" << endl;
        }
        for (int i = 56; i <= 60; i++)
        {
            writeFile << "-1 " << i << " 1 1;" << endl;
        }
        for (int i = 61; i <= 65; i++)
        {
            writeFile << "-1 " << i << " 0 1;" << endl;
        }
        writeFile << "-1 66 1 1;" << endl;
        writeFile << "-1 67 1 1;" << endl;
        writeFile << "-1 68 0 1;" << endl;

        ///Block coming down at start
        writeFile << "-1 50 3 0;" << endl;
        writeFile << "-1 49 4 1;" << endl;
        writeFile << "-1 50 4 1;" << endl;

        ///Pillar under blocks at start
        writeFile << "-1 50 5 4;" << endl;
        writeFile << "-1 50 6 3;" << endl;

        ///Floating platform
        writeFile << "-1 66 4 0;" << endl;
        writeFile << "-1 67 4 0;" << endl;
        writeFile << "-1 66 7 1;" << endl;
        writeFile << "-1 67 7 1;" << endl;

        ///Pillars under floating platform
        writeFile << "-1 66 8 4;" << endl;
        writeFile << "-1 66 9 3;" << endl;
        writeFile << "-1 67 8 4;" << endl;
        writeFile << "-1 67 9 3;" << endl;

        ///Pillars above floating platform
        writeFile << "-1 66 2 4;" << endl;
        writeFile << "-1 66 3 2;" << endl;
        writeFile << "-1 66 4 3;" << endl;
        writeFile << "-1 67 2 4;" << endl;
        writeFile << "-1 67 3 2;" << endl;
        writeFile << "-1 67 4 3;" << endl;

        ///Blocks at end
        writeFile << "-1 78 0 1;" << endl;
        writeFile << "-1 79 4 1;" << endl;
        writeFile << "-1 80 4 1;" << endl;

        ///Pillar at end
        writeFile << "-1 79 5 4;" << endl;
        writeFile << "-1 79 6 3;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 10; i <= 12; i++)
        {
            for (int j = 49; j <= 80; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Ground platforms
        for (int i = 7; i <= 12; i++)
        {
            for (int j = 49; j <= 54; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }
        for (int i = 7; i <= 12; i++)
        {
            writeFile << "0 56 " << i << " 0;" << endl;
            writeFile << "0 57 " << i << " 0;" << endl;
        }
        for (int i = 7; i <= 12; i++)
        {
            writeFile << "0 59 " << i << " 0;" << endl;
            writeFile << "0 60 " << i << " 0;" << endl;
        }
        for (int i = 7; i <= 12; i++)
        {
            for (int j = 62; j <= 64; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }
        for (int i = 7; i <= 12; i++)
        {
            for (int j = 69; j <= 80; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Ceiling
        for (int i = 49; i <= 68; i++)
        {
            writeFile << "0 " << i << " 0 0;" << endl;
        }
        for (int i = 56; i <= 60; i++)
        {
            writeFile << "0 " << i << " 1 0;" << endl;
        }
        writeFile << "0 66 1 0;" << endl;
        writeFile << "0 67 1 0;" << endl;

        ///Blocks coming down at start
        for (int i = 1; i <= 4; i++)
        {
            writeFile << "0 49 " << i << " 0;" << endl;
        }
        writeFile << "0 50 4 0;" << endl;

        ///Blocks at end
        writeFile << "0 78 0 0;" << endl;
        for (int i = 0; i <= 4; i++)
        {
            writeFile << "0 79 " << i << " 0;" << endl;
            writeFile << "0 80 " << i << " 0;" << endl;
        }

        ///Floating platform
        for (int i = 5; i <= 7; i++)
        {
            writeFile << "0 66 " << i << " 0;" << endl;
            writeFile << "0 67 " << i << " 0;" << endl;
        }

        ///Spikes
        writeFile << "1 55 9 0;" << endl;
        writeFile << "1 58 9 0;" << endl;
        writeFile << "1 61 9 0;" << endl;

        ///Room -2--------------------------------------------------
        writeFile << "///Room -2" << endl;

        ///Decorations----------
        ///Ground platforms
        for (int i = -49; i >= -54; i--)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }
        writeFile << "-1 -56 6 0;" << endl;
        writeFile << "-1 -57 6 0;" << endl;
        writeFile << "-1 -59 6 0;" << endl;
        writeFile << "-1 -60 6 0;" << endl;
        for (int i = -62; i >= -64; i--)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }
        for (int i = -69; i >= -80; i--)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        ///Pits
        writeFile << "-1 -55 9 0;" << endl;
        writeFile << "-1 -58 9 0;" << endl;
        writeFile << "-1 -61 9 0;" << endl;
        for (int i = -65; i >= -68; i--)
        {
            writeFile << "-1 " << i << " 9 0;" << endl;
        }

        ///Ceiling
        for (int i = -50; i >= -55; i--)
        {
            writeFile << "-1 " << i << " 0 1;" << endl;
        }
        for (int i = -56; i >= -60; i--)
        {
            writeFile << "-1 " << i << " 1 1;" << endl;
        }
        for (int i = -61; i >= -65; i--)
        {
            writeFile << "-1 " << i << " 0 1;" << endl;
        }
        writeFile << "-1 -66 1 1;" << endl;
        writeFile << "-1 -67 1 1;" << endl;
        writeFile << "-1 -68 0 1;" << endl;

        ///Block coming down at start
        writeFile << "-1 -50 3 0;" << endl;
        writeFile << "-1 -49 4 1;" << endl;
        writeFile << "-1 -50 4 1;" << endl;

        ///Pillar under blocks at start
        writeFile << "-1 -50 5 4;" << endl;
        writeFile << "-1 -50 6 3;" << endl;

        ///Floating platform
        writeFile << "-1 -66 4 0;" << endl;
        writeFile << "-1 -67 4 0;" << endl;
        writeFile << "-1 -66 7 1;" << endl;
        writeFile << "-1 -67 7 1;" << endl;

        ///Pillars under floating platform
        writeFile << "-1 -66 8 4;" << endl;
        writeFile << "-1 -66 9 3;" << endl;
        writeFile << "-1 -67 8 4;" << endl;
        writeFile << "-1 -67 9 3;" << endl;

        ///Pillars above floating platform
        writeFile << "-1 -66 2 4;" << endl;
        writeFile << "-1 -66 3 2;" << endl;
        writeFile << "-1 -66 4 3;" << endl;
        writeFile << "-1 -67 2 4;" << endl;
        writeFile << "-1 -67 3 2;" << endl;
        writeFile << "-1 -67 4 3;" << endl;

        ///Blocks at end
        writeFile << "-1 -78 0 1;" << endl;
        writeFile << "-1 -79 4 1;" << endl;
        writeFile << "-1 -80 4 1;" << endl;

        ///Pillar at end
        writeFile << "-1 -79 5 4;" << endl;
        writeFile << "-1 -79 6 3;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 10; i <= 12; i++)
        {
            for (int j = -49; j >= -80; j--)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Ground platforms
        for (int i = 7; i <= 12; i++)
        {
            for (int j = -49; j >= -54; j--)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }
        for (int i = 7; i <= 12; i++)
        {
            writeFile << "0 -56 " << i << " 0;" << endl;
            writeFile << "0 -57 " << i << " 0;" << endl;
        }
        for (int i = 7; i <= 12; i++)
        {
            writeFile << "0 -59 " << i << " 0;" << endl;
            writeFile << "0 -60 " << i << " 0;" << endl;
        }
        for (int i = 7; i <= 12; i++)
        {
            for (int j = -62; j >= -64; j--)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }
        for (int i = 7; i <= 12; i++)
        {
            for (int j = -69; j >= -80; j--)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Ceiling
        for (int i = -49; i >= -68; i--)
        {
            writeFile << "0 " << i << " 0 0;" << endl;
        }
        for (int i = -56; i >= -60; i--)
        {
            writeFile << "0 " << i << " 1 0;" << endl;
        }
        writeFile << "0 -66 1 0;" << endl;
        writeFile << "0 -67 1 0;" << endl;

        ///Blocks coming down at start
        for (int i = 1; i <= 4; i++)
        {
            writeFile << "0 -49 " << i << " 0;" << endl;
        }
        writeFile << "0 -50 4 0;" << endl;

        ///Blocks at end
        writeFile << "0 -78 0 0;" << endl;
        for (int i = 0; i <= 4; i++)
        {
            writeFile << "0 -79 " << i << " 0;" << endl;
            writeFile << "0 -80 " << i << " 0;" << endl;
        }

        ///Floating platform
        for (int i = 5; i <= 7; i++)
        {
            writeFile << "0 -66 " << i << " 0;" << endl;
            writeFile << "0 -67 " << i << " 0;" << endl;
        }

        ///Spikes
        writeFile << "1 -55 9 0;" << endl;
        writeFile << "1 -58 9 0;" << endl;
        writeFile << "1 -61 9 0;" << endl;

        ///Room 3 (Victory)--------------------------------------------------
        ///Decorations----------
        for (int i = 81; i <= 85; i++)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        ///Ceiling on blocks at start
        writeFile << "-1 81 4 1;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 7; i <= 12; i++)
        {
            for (int j = 81; j <= 85; j++)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Blocks coming down
        for (int i = 0; i <= 4; i++)
        {
            writeFile << "0 81 " << i << " 0;" << endl;
        }

        ///Room -3 (Victory)--------------------------------------------------
        ///Decorations----------
        for (int i = -81; i >= -85; i--)
        {
            writeFile << "-1 " << i << " 6 0;" << endl;
        }

        ///Ceiling on blocks at start
        writeFile << "-1 -81 4 1;" << endl;

        ///Blocks----------
        ///Mass ground
        for (int i = 7; i <= 12; i++)
        {
            for (int j = -81; j >= -85; j--)
            {
                writeFile << "0 " << j << " " << i << " 0;" << endl;
            }
        }

        ///Blocks coming down
        for (int i = 0; i <= 4; i++)
        {
            writeFile << "0 -81 " << i << " 0;" << endl;
        }

        ///Test--------------------------------------------------
        writeFile << "///Test" << endl;

        ///Close file--------------------------------------------------
        writeFile.close();
    }
    else cout << "Unable to open file";
    */

    ifstream levelFile(currentLevel);

    ///Read file--------------------------------------------------
    if (levelFile.is_open())
    {
        ///Loop through each line in the text file
        while (getline(levelFile, line))
        {
            ///Loop through each character of the current line being scanned
            for (int i = 0; i < line.size(); i++)
            {
                ///Check for comments
                if (line[0] == '/' && line[1] == '/')
                {
                    break;
                }
                ///If the current character being scanned is a number, add it to the currentParam variable
                else if (line[i] != ' ' && line[i] != ';')
                {
                    currentParam += line[i];
                }
                ///If it is not, then apply the last currentParam
                else
                {
                    if (paramCounter == 0)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.index = intParam;
                    }
                    else if (paramCounter == 1)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.x = intParam;
                    }
                    else if (paramCounter == 2)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.y = intParam;
                    }
                    else if (paramCounter == 3)
                    {
                        stringstream s(currentParam);
                        s >> intParam;
                        tmpAdd.type = intParam;
                    }
                    ///Reset for next loop
                    currentParam = "";
                    paramCounter++;
                }
            }

            ///Create blocks based on parameters
            ///-1 = decorations
            if (tmpAdd.index == -1)
            {
                decorations.push_back(Decoration(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f), tmpAdd.type));
            }
            else if (tmpAdd.index == 0)
            {
                blocks.push_back(Block(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }
            else if (tmpAdd.index == 1)
            {
                spikes.push_back(Spike(sf::Vector2f(tmpAdd.x * 32.0f, tmpAdd.y * 32.0f)));
            }

            ///Reset for next loop
            paramCounter = 0;
            tmpAdd.index = -1;
            tmpAdd.x = -1;
            tmpAdd.y = -1;
        }
        ///Close the file when finished
        levelFile.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    ///Reset view
    viewPosition.x = 0.0f;

    /*
    ///Update music
    if (level == 11)
    {
        requestedMusic = "overworld";
    }

    ///Reset player
    players[0].Reset();
    */
}
