//Converts Plaintext to ciphertext usings a 26 digit key

#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


int check_key(string keys);


int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        printf("Must have a key\n");
        return 1;
    }
    
    //Key validation
    string key = argv[1];
    int length = strlen(key);
    
    
    if (length != 26)
    {
        printf("Key must be 26 digits!\n");
        return 1;
    }
    //Last key validation
    int check = check_key(key);
    if (check == 1)
    {
        printf("Your key is not valid!\n");
        return 1;
    }
    
    
    
    //Will be a command arguement
    string text = get_string("plaintext: ");
    
   

    //Creates arrays for capitalized and non-capitalized alphabets
    int alf[26];
    for (int j = 0; j < 26; j++)
    {
        alf[j] = 65 + j;
    }
    int alf_s[26];
    for (int z = 0; z < 26; z++)
    {
        alf_s[z] = 97 + z;
    }

    //Calculates the delta needed for each letter based on the code
    int delta[26];
    for (int i = 0; i < 26; i++)
    {
        //delta for capital letter key
        if (key[i] >= 65 && key[i] <= 90)
        {
            delta[i] = key[i] - alf[i];
        }
        else if (key[i] >= 97 && key[i] <= 122)
        {
            delta[i] = key[i] - alf_s[i];
        }
    }

    //Creates ciphertext array
    int n = strlen(text);
    int ciphertext[n];


    printf("ciphertext: ");
    for (int l = 0 ; l < n; l++)
    {
        //Changes text based on key for capitalized alphabet
        if (text[l] >= 65 && text[l] <= 90)
        {
            for (int m = 0; m < 26; m++)
            {
                if (text[l] == alf[m])
                {
                    ciphertext[l] = text[l] + delta[m];

                    //wraps capitalized alphabet
                    if (ciphertext[l] > 90)
                    {
                        ciphertext[l] = 64 + (ciphertext[l] - 90);
                    }

                }
            }
        }

        //Changes text based on key for non-capitalized alphabet
        else if (text[l] >= 97 && text[l] <= 122)
        {
            for (int o = 0; o < 26; o++)
            {
                if (text[l] == alf_s[o])
                {
                    ciphertext[l] = text[l] + delta[o];

                    //wraps non-capitalized alphabet
                    if (ciphertext[l] > 122)
                    {
                        ciphertext[l] = 96 + (ciphertext[l] - 122);
                    }
                }
            }
        }

        //Leaves text as is if not a letter
        else
        {
            ciphertext[l] = text[l];
        }

        printf("%c", ciphertext[l]);
    }
    printf("\n");

}

int check_key(string keys)
{
    //creates arrays of lower & uppercase letters
    int alf[26];
    for (int j = 0; j < 26; j++)
    {
        alf[j] = 65 + j;
    }
    int alf_s[26];
    for (int z = 0; z < 26; z++)
    {
        alf_s[z] = 97 + z;
    }
    
    
    for (int i = 0, n = strlen(keys); i < n; i++)
    {
        if (keys[i] >= 97 && keys[i] <= 122)
        {
            keys[i] = keys[i] - 32;
        }
        
        else if (keys[i] >= 65 && keys[i] <= 90)
        {
            
        }
        
        else
        {
            return 1;
        }
        
    }
    
    int j = 0;
    int k = 0;
    do
    {
        if (alf[j] != keys[k])
        {
            k++;
        }
        
        else
        {
            j++;
            k = 0;
        }
        
        if (k > 26)
        {
            return 1;
        }
        
        
    }
    while (j < 26);

    
    
    return 0;
}