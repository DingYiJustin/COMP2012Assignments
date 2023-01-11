//submit this file only
#include "decimal.h"
using namespace std;
//add your code below
//see FAQ for what you can/cannot do 

int numberToChar(int num)
{
    return num+'0';
}
int charToNumber(char character)
{
    return character-'0';
}

Decimal::Decimal(){
    content = new char[1];
    content[0] = '0';
    size = 1;
}

Decimal::Decimal(int input)
{
    bool signCheck = false;
    size = 0;
    
    int copyInput = input;
    if(copyInput<0)
    {
        signCheck = true;
        copyInput = -copyInput;
        size++;
    }
        
    while(copyInput>0)
    {
        copyInput = copyInput/10;
        size++;
    }

    content = new char[size];
    if(signCheck)
    {
        content[0] = '-';
        input = -input;
        for(int i = 1; i<size; i++)
        {
            int divid = 1;
            for(int j=0;j<size-i-1;j++)
                divid*=10;
            content[i] = input/divid+'0';
            input = input - input/divid*divid;
        }
    }
    else
    {
        for(int i = 0; i<size; i++)
        {
            int divid = 1;
            for(int j=0;j<size-i-1;j++)
                divid*=10;
            content[i] = input/divid+'0';
            input = input - input/divid*divid;
        }
    }

}

Decimal::Decimal(const char* input)
{
    size = 0;
    while(input[size]!='\0')
    {
        size++;
    }
    content = new char[size];
    for(int i = 0; i<size; i++)
        content[i] = input[i]; 
}

Decimal::Decimal(const Decimal& another)
{
    this->size=another.size;
    this->content = new char[size];
    for(int i = 0; i<size; i++)
    {
        this->content[i] = another.content[i];
    }
}


Decimal::~Decimal()
{
    delete[] content;
    size = 0;
    content = nullptr;
}

bool Decimal::isNegative() const
{
    return (content[0] == '-')? true:false;
}

Decimal Decimal::flipSign() const
{
    if(content[0] == '0' && size == 1)
    {
        return Decimal(0);
    }
    else if(content[0]=='-')
    {
        char* tempContent = new char[size];
        tempContent[size-1] = '\0';
        for(int i=0; i<size-1; i++)
        {
            tempContent[i] = content[i+1];
        }
        
        Decimal temp(tempContent);
        delete[] tempContent;
        return temp;
    }
    else
    {
        char* tempContent = new char[size+2];
        tempContent[0] = '-';
        for(int i=1; i<size+1; i++)
        {
            tempContent[i] = content[i-1];
        }
        tempContent[size+1] = '\0';
        Decimal temp(tempContent);
        delete[] tempContent;
        return temp;
    }
}

bool Decimal::isLargerThan(const Decimal& another) const
{
    if(content[0] == '0' && size == 1)
    {
        if(another.content[0]== '0' && another.size == 1)
            return false;
        else if(another.content[0]=='-')
            return true;
        else
            return false;
    }
    else if(content[0]=='-')
    {
        if(another.content[0]== '0' && another.size == 1)
            return false;
        else if(another.content[0]=='-')
        {
            int digitBeforeForThis = countDigitsBeforeDP();
            int digitBeforeForAnother = another.countDigitsBeforeDP();

            if(digitBeforeForThis>digitBeforeForAnother)
                return false;
            else if(digitBeforeForAnother>digitBeforeForThis)
                return true;

            for(int i = 0; i<=countDigitsBeforeDP(); i++)
            {
                if(content[i]==another.content[i])
                    continue;
                else
                {
                    if(content[i]>another.content[i])
                        return false;
                    else
                        return true;
                }
            }

            int digitafter = (countDigitsAfterDP()>=another.countDigitsAfterDP())?another.countDigitsAfterDP():countDigitsAfterDP();
            for(int i = 0; i<digitafter; i++)
            {
                if(content[digitBeforeForThis+2+i]==another.content[digitBeforeForAnother+2+i])
                    continue;
                else
                {
                    if(content[digitBeforeForThis+2+i]>another.content[digitBeforeForAnother+2+i])
                        return false;
                    else
                        return true;
                }
            }
            if(countDigitsAfterDP()>=another.countDigitsAfterDP())
                return false;
            else 
                return true;
            
        }
        else
            return false;
        return false;
    }
    else
    {
        if(another.content[0]== '0' && another.size == 1)
            return true;
        else if(another.content[0]=='-')
        {
            return true;
        }
        else
        {
            int digitBeforeForThis = countDigitsBeforeDP();
            int digitBeforeForAnother = another.countDigitsBeforeDP();

            if(digitBeforeForThis>digitBeforeForAnother)
                return true;
            else if(digitBeforeForAnother>digitBeforeForThis)
                return false;
            for(int i = 0; i<countDigitsBeforeDP(); i++)
            {
                if(content[i]==another.content[i])
                    continue;
                else
                {
                    if(content[i]>another.content[i])
                        return true;
                    else
                        return false;
                }
            }

            int digitafter = (countDigitsAfterDP()>=another.countDigitsAfterDP())?another.countDigitsAfterDP():countDigitsAfterDP();
            for(int i = 0; i<digitafter; i++)
            {
                if(content[digitBeforeForThis+1+i]==another.content[digitBeforeForAnother+1+i])
                {
                    continue;
                }   
                else
                {
                    if(content[digitBeforeForThis+1+i]>another.content[digitBeforeForAnother+1+i])
                        return true;
                    else
                        return false;
                }
                
            }
            if(countDigitsAfterDP()>=another.countDigitsAfterDP())
                return true;
            else 
                return false;
            
        }
        return false;
    }
}


Decimal Decimal::add(const Decimal& another) const
{
    if(content[0] == '0' && size == 1)
    {
        return Decimal(another);
    }
    if(another.content[0] == '0' && another.size == 1)
    {
        return *this;
    }
    else if(content[0] == '-' && another.content[0] == '-')
    {
        
            int numOfDigitsBeforeDecimalForThis = countDigitsBeforeDP();
            int numOfDigitsBeforeDecimalForAnother = another.countDigitsBeforeDP();
            int numofDigitsAfterDecimalForThis = countDigitsAfterDP();
            int numofDigitsAfterDecimalForAnother = another.countDigitsAfterDP();
            int digitForDecimal = 0;
            int numofDigitsForLimit = 0;
            bool pointcheckforThis = false;
            bool pointcheckforAnother = false;
            bool passedlast = false;
            bool havelimit =false;
            bool exceeded = false;
            bool needToAdd = false;

            for(int i=1; i<size; i++)
            {
                if(content[i] == '.')
                {
                    pointcheckforThis = true;
                    break;
                }
            }

            for(int i=1; i<size; i++)
            {
                if(another.content[i] == '.')
                {
                    pointcheckforAnother = true;
                    break;
                }
                    
                //numOfDigitsBeforeDecimalForAnother++;
            }
            //numofDigitsAfterDecimalForAnother = (pointcheckforAnother)? (size - 2 - numofDigitsAfterDecimalForAnother):(size - 2 - numofDigitsAfterDecimalForAnother);
            int newSize = 2+((numofDigitsAfterDecimalForThis>=numofDigitsAfterDecimalForAnother) ? numofDigitsAfterDecimalForThis:numofDigitsAfterDecimalForAnother)
                            +((numOfDigitsBeforeDecimalForThis>=numOfDigitsBeforeDecimalForAnother)?numOfDigitsBeforeDecimalForThis:numOfDigitsBeforeDecimalForAnother);
            digitForDecimal = 1+((numOfDigitsBeforeDecimalForThis>=numOfDigitsBeforeDecimalForAnother)?numOfDigitsBeforeDecimalForThis:numOfDigitsBeforeDecimalForAnother);
            
            if(!(pointcheckforThis||pointcheckforAnother))
            {
                newSize--;
            }
            
            char* tempReturnValue = new char[newSize];
            
            if(pointcheckforThis&&pointcheckforAnother)
            {
                if(numofDigitsAfterDecimalForAnother>numofDigitsAfterDecimalForThis)
                {
                    for(int i=newSize-1; i>digitForDecimal+numofDigitsAfterDecimalForThis;i--)
                    {
                        tempReturnValue[i] = another.content[another.size-1+(i-newSize+1)];
                    }
                    for(int i=digitForDecimal+numofDigitsAfterDecimalForThis; i>(digitForDecimal);i--)
                    {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }
                        tempReturnValue[i] = numberToChar(temp);
                    }
                }   
                else if(numofDigitsAfterDecimalForAnother<numofDigitsAfterDecimalForThis)
                {
                    for(int i=newSize-1; i>digitForDecimal+numofDigitsAfterDecimalForAnother;i--)
                    {
                        tempReturnValue[i] = content[size-1+(i-newSize+1)];
                    }
                    for(int i=digitForDecimal+numofDigitsAfterDecimalForAnother; i>(digitForDecimal);i--)
                    {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }
                        tempReturnValue[i] = numberToChar(temp);
                    }
                }
                else
                {
                    for(int i=newSize-1; i>digitForDecimal;i--)
                    {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                        if(!passedlast)
                        {
                            if(needToAdd)
                            {
                                temp++;
                                needToAdd=false;
                            }
                                
                            if(temp>=10)
                            {
                                temp%=10;
                                needToAdd=true;
                            }
                            if(temp == 0)
                            {
                                tempReturnValue[i] = '\0';
                                havelimit = true;
                                numofDigitsForLimit++;
                            }
                            else
                                tempReturnValue[i] = numberToChar(temp);
                        }
                        else
                        {
                            int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                            if(needToAdd)
                            {
                                temp++;
                                needToAdd=false;
                            }
                                
                            if(temp>=10)
                            {
                                temp%=10;
                                needToAdd=true;
                            }
                            tempReturnValue[i] = numberToChar(temp);
                        }
                        
                    }
                }

                tempReturnValue[digitForDecimal] = '.';

            }
            else
            {
                if(pointcheckforAnother)
                {
                    for(int i=digitForDecimal+1;i<newSize;i++)
                    {
                        tempReturnValue[i] = another.content[numOfDigitsBeforeDecimalForAnother+2+(i-(digitForDecimal+1))];
                    }
                }
                else if(pointcheckforThis)
                {
                    for(int i=digitForDecimal+1;i<newSize;i++)
                    {
                        tempReturnValue[i] = content[numOfDigitsBeforeDecimalForThis+2+(i-(digitForDecimal+1))];
                    }
                }
                tempReturnValue[digitForDecimal] = '.';
            }
            
            if(numOfDigitsBeforeDecimalForThis>=numOfDigitsBeforeDecimalForAnother)
            {
                for(int i= digitForDecimal-1; i>0;i--)
                {
                    int temp;
                    if(numOfDigitsBeforeDecimalForAnother-(digitForDecimal-1-i)>0)
                        temp = charToNumber(content[i]) +charToNumber(another.content[numofDigitsAfterDecimalForAnother-(digitForDecimal-1-i)]);
                    else
                        temp = charToNumber(content[i]);
                    if(i!=1)
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                    else
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            exceeded = true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                            
                }
            }
            else
            {
                for(int i= digitForDecimal-1; i>0;i--)
                {
                    int temp;
                    if(numOfDigitsBeforeDecimalForThis-(digitForDecimal-1-i)>0)
                        temp = charToNumber(content[numOfDigitsBeforeDecimalForThis-(digitForDecimal-1-i)]) +charToNumber(another.content[i]);
                    else
                        temp = charToNumber(another.content[i]);
                    if(i!=1)
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                    else
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            exceeded = true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                            
                }
            }
            tempReturnValue[0] = '-';

            int newSizeforReturn;
            if(exceeded&&havelimit)
            {
                newSizeforReturn = newSize+1-numofDigitsForLimit;
                char* returnValue = new char[newSizeforReturn+1];
                returnValue[0] = '-';
                returnValue[1] = '1';
                for(int i=2;i<newSizeforReturn;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSizeforReturn] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
            else if(exceeded)
            {
                newSizeforReturn = newSize+1;
                char* returnValue = new char[newSizeforReturn+1];
                returnValue[0] = '-';
                returnValue[1] = '1';
                for(int i=2;i<newSizeforReturn;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSizeforReturn] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
            else if(havelimit)
            {
                newSizeforReturn = newSize-numofDigitsForLimit;
                char* returnValue = new char[newSizeforReturn+1];
                for(int i=0;i<newSizeforReturn;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSizeforReturn] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
            else
            {
                char* returnValue = new char[newSize+1];
                for(int i=0;i<newSize;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSize] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
    }
    else if(another.content[0] != '-' && content[0] != '-')
    {
            int numOfDigitsBeforeDecimalForThis = countDigitsBeforeDP();
            int numOfDigitsBeforeDecimalForAnother = another.countDigitsBeforeDP();
            int numofDigitsAfterDecimalForThis = countDigitsAfterDP();
            int numofDigitsAfterDecimalForAnother = another.countDigitsAfterDP();
            int digitForDecimal = 0;
            int numofDigitsForLimit = 0;
            bool pointcheckforThis = false;
            bool pointcheckforAnother = false;
            bool passedlast = false;
            bool havelimit =false;
            bool exceeded = false;
            bool needToAdd = false;

            for(int i=1; i<size; i++)
            {
                if(content[i] == '.')
                {
                    pointcheckforThis = true;
                    break;
                }
                
            }
            for(int i=1; i<size; i++)
            {
                if(another.content[i] == '.')
                {
                    pointcheckforAnother = true;
                    break;
                }
                    
                
            }
            int newSize = 1+((numofDigitsAfterDecimalForThis>=numofDigitsAfterDecimalForAnother) ? numofDigitsAfterDecimalForThis:numofDigitsAfterDecimalForAnother)
                            +((numOfDigitsBeforeDecimalForThis>=numOfDigitsBeforeDecimalForAnother)?numOfDigitsBeforeDecimalForThis:numOfDigitsBeforeDecimalForAnother);
            digitForDecimal = ((numOfDigitsBeforeDecimalForThis>=numOfDigitsBeforeDecimalForAnother)?numOfDigitsBeforeDecimalForThis:numOfDigitsBeforeDecimalForAnother);
            
            if(!(pointcheckforThis||pointcheckforAnother))
            {
                newSize--;
            }
            
            char* tempReturnValue = new char[newSize];
            
            if(pointcheckforThis&&pointcheckforAnother)
            {
                if(numofDigitsAfterDecimalForAnother>numofDigitsAfterDecimalForThis)
                {
                    for(int i=newSize-1; i>digitForDecimal+numofDigitsAfterDecimalForThis;i--)
                    {
                        tempReturnValue[i] = another.content[another.size-1+(i-newSize+1)];
                    }
                    for(int i=digitForDecimal+numofDigitsAfterDecimalForThis; i>(digitForDecimal);i--)
                    {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }
                        tempReturnValue[i] = numberToChar(temp);
                    }
                }   
                else if(numofDigitsAfterDecimalForAnother<numofDigitsAfterDecimalForThis)
                {
                    for(int i=newSize-1; i>digitForDecimal+numofDigitsAfterDecimalForAnother;i--)
                    {
                        tempReturnValue[i] = content[size-1+(i-newSize+1)];
                    }
                    for(int i=digitForDecimal+numofDigitsAfterDecimalForAnother; i>(digitForDecimal);i--)
                    {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }
                        tempReturnValue[i] = numberToChar(temp);
                    }
                }
                else
                {
                    for(int i=newSize-1; i>digitForDecimal;i--)
                    {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                        if(!passedlast)
                        {
                            if(needToAdd)
                            {
                                temp++;
                                needToAdd=false;
                            }
                                
                            if(temp>=10)
                            {
                                temp%=10;
                                needToAdd=true;
                            }
                            if(temp == 0)
                            {
                                tempReturnValue[i] = '\0';
                                havelimit = true;
                                numofDigitsForLimit++;
                            }
                            else
                                tempReturnValue[i] = numberToChar(temp);
                        }
                        else
                        {
                            int temp = charToNumber(content[size-1+(i-newSize+1)]) +charToNumber(another.content[another.size-1+(i-newSize+1)]);
                            if(needToAdd)
                            {
                                temp++;
                                needToAdd=false;
                            }
                                
                            if(temp>=10)
                            {
                                temp%=10;
                                needToAdd=true;
                            }
                            tempReturnValue[i] = numberToChar(temp);
                        }
                        
                    }
                }

                tempReturnValue[digitForDecimal] = '.';

            }
            else
            {
                if(pointcheckforAnother)
                {
                    for(int i=digitForDecimal+1;i<newSize;i++)
                    {
                        tempReturnValue[i] = another.content[numOfDigitsBeforeDecimalForAnother+1+(i-(digitForDecimal+1))];
                    }
                }
                else if(pointcheckforThis)
                {
                    for(int i=digitForDecimal+1;i<newSize;i++)
                    {
                        tempReturnValue[i] = content[numOfDigitsBeforeDecimalForThis+1+(i-(digitForDecimal+1))];
                    }
                }
                tempReturnValue[digitForDecimal] = '.';
            }

            if(numOfDigitsBeforeDecimalForThis>=numOfDigitsBeforeDecimalForAnother)
            {
                for(int i= digitForDecimal-1; i>=0;i--)
                {
                    int temp; 
                    if(numOfDigitsBeforeDecimalForAnother-(digitForDecimal-i)>=0)
                       temp = charToNumber(content[i]) +charToNumber(another.content[numOfDigitsBeforeDecimalForAnother-(digitForDecimal-i)]);
                    else
                        temp = charToNumber(content[i]);
                    if(i!=1)
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp-=10;
                            needToAdd=true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                    else
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            exceeded = true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                            
                }
            }
            else
            {
                for(int i= digitForDecimal-1; i>=0;i--)
                {
                    int temp; 
                    if(numOfDigitsBeforeDecimalForThis-(digitForDecimal-i)>=0)
                       temp = charToNumber(content[numOfDigitsBeforeDecimalForThis-(digitForDecimal-i)]) +charToNumber(another.content[i]);
                    else
                        temp = charToNumber(another.content[i]);
                    if(i!=1)
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            needToAdd=true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                    else
                    {
                        if(needToAdd)
                        {
                            temp++;
                            needToAdd=false;
                        }
                            
                        if(temp>=10)
                        {
                            temp%=10;
                            exceeded = true;
                        }

                            tempReturnValue[i] = numberToChar(temp);
                    }
                            
                }
            }
            int newSizeforReturn;
            if(exceeded&&havelimit)
            {
                newSizeforReturn = newSize+1-numofDigitsForLimit;
                char* returnValue = new char[newSizeforReturn+1];
                returnValue[0] = '1';
                for(int i=1;i<newSizeforReturn;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSizeforReturn] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
            else if(exceeded)
            {
                newSizeforReturn = newSize+1;
                char* returnValue = new char[newSizeforReturn+1];
                returnValue[0] = '1';
                for(int i=1;i<newSizeforReturn;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSizeforReturn] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
            else if(havelimit)
            {
                newSizeforReturn = newSize-numofDigitsForLimit;
                char* returnValue = new char[newSizeforReturn+1];
                for(int i=0;i<newSizeforReturn;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSizeforReturn] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
            else
            {
                char* returnValue = new char[newSize+1];
                for(int i=0;i<newSize;i++)
                {
                    returnValue[i] = tempReturnValue[i];
                }
                returnValue[newSize] = '\0';
                Decimal tempObject(returnValue);
                delete[] tempReturnValue;
                delete[] returnValue;
                return tempObject;
            }
    }
    else
    {
        if(this->isNegative())
            return another.subtract(this->flipSign());
        return this->subtract(another.flipSign());
    }
    
}


void Decimal::addToSelf(const Decimal& another)
{
    Decimal temp = add(another);
    char* newContent = new char[temp.size];
    for(int i = 0; i< temp.size; i++)
        newContent[i] = temp.content[i];
    delete[] content;
    content = newContent;
    size = temp.size;
    return;
}


Decimal Decimal::multiplyByPowerOfTen(int power) const
{
    int indexOfDecimal = 0;
    for(int i = 0; i<size; i++)
    {
        if(content[i] == '.')
        {
            indexOfDecimal = i;
            break;
        }
    }

    if(indexOfDecimal == 0)
    {
        char* temp = new char[size + power+1];
        for(int i = 0; i<size; i++)
        {
            temp[i] = content[i];
        }
        for(int i = size; i<size+power;i++)
        {
            temp[i] = 0;
        }
        temp[size+power] = '\0';
        Decimal returnObj(temp);
        delete[] temp;
        return returnObj;
    }
    else
    {
        int digitsAfterDecimal = countDigitsAfterDP();
        if(digitsAfterDecimal>power)
        {
            char* temp = new char[size+1];
            for(int i = 0; i<size; i++)
            {
                temp[i] = content[i];
            }
            for(int i = size; i<size+power;i++)
            {
                temp[i] = 0;
            }
            temp[size] = '\0';
            for(int i = 0; i<power; i++)
            {
                char temper = temp[indexOfDecimal+i];
                temp[indexOfDecimal+i] = temp[indexOfDecimal+i+1];
                temp[indexOfDecimal+i+1] = temper;
            }
            Decimal returnObj(temp);
            delete[] temp;
            return returnObj;
        }
        else
        {
            int newdigit = digitsAfterDecimal - power;
            char* temp = new char[size+newdigit];
            temp[size+newdigit-1] = '\0';
            for(int i = 0; i<indexOfDecimal; i++)
            {
                temp[i] = content[i];
            }
            for(int i = indexOfDecimal+1; i<size;i++)
            {
                temp[i-1] = content[i];
            }
            for(int i = size-1; i<size+newdigit-1; i++)
            {
                temp[i] = 0;
            }
            Decimal returnObj(temp);
            delete[] temp;
            return returnObj;
        }
    }
}

Decimal Decimal::multiplyBySingleDigit(int multiplier) const
{
    if(multiplier == 0)
        return Decimal(0);

    int numberNeededToBeAdd = 0;
    bool passedlast = false;
    char* tempValue = new char[size+1];
    tempValue[size] = '\0';
    if(isNegative())
    {
        int digitsBeforeDP = countDigitsBeforeDP()+1;
        if(digitsBeforeDP>1)
        {
            for(int i = size-1; i>digitsBeforeDP; i--)
            {
                int temp = charToNumber(content[i])*multiplier;
                temp+=numberNeededToBeAdd;
                numberNeededToBeAdd = 0;
                if(temp>=10)
                {
                    numberNeededToBeAdd = temp/10;
                    temp%=10;
                    if(!passedlast && temp == 0)
                    {
                        tempValue[i] = '\0';
                        continue;
                    }
                }
                tempValue[i] = temp;
                passedlast = true;
            }

            for(int i = digitsBeforeDP-1; i>0; i--)
            {
                int temp = charToNumber(content[i])*multiplier;
                temp+=numberNeededToBeAdd;
                numberNeededToBeAdd = 0;
                if(temp>=10)
                {
                    numberNeededToBeAdd = temp/10;
                    temp%=10;
                }
                tempValue[i] = temp;
            }
            tempValue[0] = '-';
            if(numberNeededToBeAdd)
            {
                char* returnValue = new char[size+2];
                returnValue[0] = '-';
                returnValue[1] = numberNeededToBeAdd;
                for(int i=2;i<size+1;i++)
                    returnValue[i] = tempValue[i-1];
                Decimal tempObj(returnValue);
                delete[] returnValue;
                delete[] tempValue;
                return tempObj;
            }
            else
            {
                Decimal tempObj(tempValue);
                delete[] tempValue;
                return tempObj;
            }
        }
        else
        {   
            for(int i = size-1; i>0; i--)
            {
                int temp = charToNumber(content[i])*multiplier;
                temp+=numberNeededToBeAdd;
                numberNeededToBeAdd = 0;
                if(temp>=10)
                {
                    numberNeededToBeAdd = temp/10;
                    temp%=10;
                }
                tempValue[i] = temp;
            }
            tempValue[0] = '-';
            if(numberNeededToBeAdd)
            {
                char* returnValue = new char[size+2];
                returnValue[0] = '-';
                returnValue[1] = numberNeededToBeAdd;
                for(int i=2;i<size+1;i++)
                    returnValue[i] = tempValue[i-1];
                Decimal tempObj(returnValue);
                delete[] returnValue;
                delete[] tempValue;
                return tempObj;
            }
            else
            {
                Decimal tempObj(tempValue);
                delete[] tempValue;
                return tempObj;
            }
        }
    }
    else
    {
        int digitsBeforeDP = countDigitsBeforeDP();
        if(digitsBeforeDP>0)
        {
            for(int i = size-1; i>digitsBeforeDP; i--)
            {
                int temp = charToNumber(content[i])*multiplier;
                temp+=numberNeededToBeAdd;
                numberNeededToBeAdd = 0;
                if(temp>=10)
                {
                    numberNeededToBeAdd = temp/10;
                    temp%=10;
                    if(!passedlast && temp == 0)
                    {
                        tempValue[i] = '\0';
                        continue;
                    }
                }
                tempValue[i] = temp;
                passedlast = true;
            }

            for(int i = digitsBeforeDP-1; i>=0; i--)
            {
                int temp = charToNumber(content[i])*multiplier;
                temp+=numberNeededToBeAdd;
                numberNeededToBeAdd = 0;
                if(temp>=10)
                {
                    numberNeededToBeAdd = temp/10;
                    temp%=10;
                }
                tempValue[i] = temp;
            }
            
            if(numberNeededToBeAdd)
            {
                char* returnValue = new char[size+2];
                returnValue[0] = numberNeededToBeAdd;
                for(int i=1;i<size+1;i++)
                    returnValue[i] = tempValue[i-1];
                Decimal tempObj(returnValue);
                delete[] returnValue;
                delete[] tempValue;
                return tempObj;
            }
            else
            {
                Decimal tempObj(tempValue);
                delete[] tempValue;
                return tempObj;
            }
        }
        else
        {

            for(int i = size-1; i>=0; i--)
            {
                int temp = charToNumber(content[i])*multiplier;
                temp+=numberNeededToBeAdd;
                numberNeededToBeAdd = 0;
                if(temp>=10)
                {
                    numberNeededToBeAdd = temp/10;
                    temp%=10;
                }
                tempValue[i] = temp;
            }
            
            if(numberNeededToBeAdd)
            {
                char* returnValue = new char[size+2];
                returnValue[0] = numberNeededToBeAdd;
                for(int i=1;i<size+1;i++)
                    returnValue[i] = tempValue[i-1];
                Decimal tempObj(returnValue);
                delete[] returnValue;
                delete[] tempValue;
                return tempObj;
            }
            else
            {
                Decimal tempObj(tempValue);
                delete[] tempValue;
                return tempObj;
            }

        }
    }
    
}

Decimal Decimal::multiply(const Decimal& another) const
{
    
    if(isNegative() && another.isNegative())
    {
        int digitAfter = another.countDigitsAfterDP();
        Decimal copyAnother((another.flipSign()).multiplyByPowerOfTen(digitAfter));
        Decimal copyThis(this->flipSign());
        Decimal returnObj(0);
        
        for(int i = copyAnother.size-1;i>=0;i++)
        {
            returnObj.addToSelf((copyThis.multiplyBySingleDigit(copyAnother.content[i])).multiplyByPowerOfTen(i-(copyAnother.size-1)));
        }

        if(digitAfter == 0)
        {
            return returnObj;
        }
            

        if(this->countDigitsAfterDP() == 0)
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            for(int i = 0; i<returnObj.size-digitAfter; i++)
            {
                temp[i] = returnObj.content[i];
            }
            temp[returnObj.size-digitAfter] = '.';
            for(int i = size-digitAfter+1;i<returnObj.size+1;i++)
            {
                temp[i] =  returnObj.content[i-1];
            }

            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
        else
        {
            for(int i = 0; i<digitAfter;i++)
            {
                char temp = returnObj.content[returnObj.countDigitsBeforeDP()-1];
                returnObj.content[returnObj.countDigitsBeforeDP()-1] = '.';
                returnObj.content[returnObj.countDigitsBeforeDP()] = temp;
            }
            return returnObj;
        }
    }
    else if(isNegative())
    {
        int digitAfter = another.countDigitsAfterDP();
        Decimal copyAnother((another).multiplyByPowerOfTen(digitAfter));
        Decimal copyThis(this->flipSign());
        Decimal returnObj(0);
        
        for(int i = copyAnother.size-1;i>=0;i++)
        {
            returnObj.addToSelf((copyThis.multiplyBySingleDigit(copyAnother.content[i])).multiplyByPowerOfTen(i-(copyAnother.size-1)));
        }

        if(digitAfter == 0)
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            temp[0] = '-';
            for(int i = 0; i<returnObj.size; i++)
            {
                temp[i+1] = returnObj.content[i];
            }
            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
            

        if(this->countDigitsAfterDP() == 0)
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            temp[0] = '-';
            for(int i = 0; i<returnObj.size-digitAfter; i++)
            {
                temp[i+1] = returnObj.content[i];
            }
            temp[returnObj.size-digitAfter+1] = '.';
            for(int i = returnObj.size-digitAfter+1;i<returnObj.size+1;i++)
            {
                temp[i+1] =  returnObj.content[i-1];
            }

            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
        else
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            temp[0] = '-';
            for(int i = 0; i<returnObj.size; i++)
            {
                temp[i+1] = returnObj.content[i];
            }

            for(int i = 0; i<digitAfter;i++)
            {
                char tempvalue = temp[returnObj.countDigitsBeforeDP()];
                temp[returnObj.countDigitsBeforeDP()] = '.';
                temp[returnObj.countDigitsBeforeDP()+1] = tempvalue;
            }
            
            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
    }
    else if(another.isNegative())
    {
        int digitAfter = another.countDigitsAfterDP();
        Decimal copyAnother((another.flipSign()).multiplyByPowerOfTen(digitAfter));
        Decimal copyThis(*this);
        Decimal returnObj(0);
        
        for(int i = copyAnother.size-1;i>=0;i++)
        {
            returnObj.addToSelf((copyThis.multiplyBySingleDigit(copyAnother.content[i])).multiplyByPowerOfTen(i-(copyAnother.size-1)));
        }

        if(digitAfter == 0)
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            temp[0] = '-';
            for(int i = 0; i<returnObj.size; i++)
            {
                temp[i+1] = returnObj.content[i];
            }
            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
            

        if(this->countDigitsAfterDP() == 0)
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            temp[0] = '-';
            for(int i = 0; i<returnObj.size-digitAfter; i++)
            {
                temp[i+1] = returnObj.content[i];
            }
            temp[returnObj.size-digitAfter+1] = '.';
            for(int i = returnObj.size-digitAfter+1;i<returnObj.size+1;i++)
            {
                temp[i+1] =  returnObj.content[i-1];
            }

            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
        else
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            temp[0] = '-';
            for(int i = 0; i<returnObj.size; i++)
            {
                temp[i+1] = returnObj.content[i];
            }

            for(int i = 0; i<digitAfter;i++)
            {
                char tempvalue = temp[returnObj.countDigitsBeforeDP()];
                temp[returnObj.countDigitsBeforeDP()] = '.';
                temp[returnObj.countDigitsBeforeDP()+1] = tempvalue;
            }
            
            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
    }
    else
    {
        int digitAfter = another.countDigitsAfterDP();
        Decimal copyAnother((another).multiplyByPowerOfTen(digitAfter));
        Decimal copyThis(*this);
        Decimal returnObj(0);
        
        for(int i = copyAnother.size-1;i>=0;i++)
        {
            returnObj.addToSelf((copyThis.multiplyBySingleDigit(copyAnother.content[i])).multiplyByPowerOfTen(i-(copyAnother.size-1)));
        }

        if(digitAfter == 0)
        {
            return returnObj;
        }
            

        if(this->countDigitsAfterDP() == 0)
        {
            char* temp = new char[returnObj.size+2];
            temp[returnObj.size+1] = '\0';
            for(int i = 0; i<returnObj.size-digitAfter; i++)
            {
                temp[i] = returnObj.content[i];
            }
            temp[returnObj.size-digitAfter] = '.';
            for(int i = size-digitAfter+1;i<returnObj.size+1;i++)
            {
                temp[i] =  returnObj.content[i-1];
            }

            Decimal tempObj(temp);
            delete[] temp;
            return tempObj;
        }
        else
        {
            for(int i = 0; i<digitAfter;i++)
            {
                char temp = returnObj.content[returnObj.countDigitsBeforeDP()-1];
                returnObj.content[returnObj.countDigitsBeforeDP()-1] = '.';
                returnObj.content[returnObj.countDigitsBeforeDP()] = temp;
            }
            return returnObj;
        }
    }
}


Decimal Decimal::subtract(const Decimal& another) const
{
    if(isNegative())
    {
        if(!another.isNegative())
            return add(another.flipSign());
        
        Decimal copyThis(this->flipSign());
        int needToDelete = 0;
        bool passedlast = false;
        int digitBeforeForThis = countDigitsBeforeDP();
        int digitAfterForThis = countDigitsAfterDP();
        int digitBeforeForAnother = another.countDigitsBeforeDP();
        int digitAfterForAnother = another.countDigitsAfterDP();

        int indexOfDecimal = (digitBeforeForAnother>=digitBeforeForThis)?digitBeforeForAnother:digitBeforeForThis;

        bool nodecimal = !(digitAfterForAnother||digitAfterForThis);

        int newSize = ((digitBeforeForAnother>=digitBeforeForThis)?digitBeforeForAnother:digitBeforeForThis)+((digitAfterForAnother>=digitAfterForThis)?digitAfterForAnother:digitAfterForThis)+1;
        if(nodecimal)
            newSize--;

        char* tempValue = new char[newSize];

        if(copyThis.isLargerThan(another))
        {
            if(digitAfterForAnother == digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal;i-- )
                {
                    int temp = charToNumber(copyThis.content[copyThis.size-1+(i-newSize+1)]) - charToNumber(another.content[another.size-1+(i-newSize+1)])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    else if(!passedlast&&temp == 0)
                    {
                        tempValue[i] = '\0';
                        continue;
                    }

                    tempValue[i] = numberToChar(temp);
                    passedlast = true;
                }
            }
            else if(digitAfterForAnother>digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForThis;i--)
                {
                    tempValue[i] = another.content[another.size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForThis; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(copyThis.content[copyThis.size-1+(i-newSize+1)]) - charToNumber(another.content[another.size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                }
            }
            else if(digitAfterForThis>digitAfterForAnother)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForAnother;i--)
                {
                    tempValue[i] = copyThis.content[copyThis.size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForAnother; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(copyThis.content[copyThis.size-1+(i-newSize+1)]) - charToNumber(another.content[another.size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                    
                }
            }
            tempValue[indexOfDecimal] = '.';

            if(digitBeforeForAnother == digitBeforeForThis)
            {
                for(int i=indexOfDecimal-1;i>=0;i--)
                {
                    int temp = charToNumber(copyThis.content[i])-charToNumber(another.content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }
            else
            {
                int gap = digitBeforeForThis-digitBeforeForAnother;
                for(int i=indexOfDecimal-1;i>indexOfDecimal-1-digitBeforeForAnother;i--)
                {
                    int temp = charToNumber(copyThis.content[i]) - charToNumber(another.content[i-gap])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }

                for(int i=indexOfDecimal-1-digitBeforeForAnother;i>=0;i--)
                {
                    int temp = charToNumber(copyThis.content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }

            bool passedfirst = false;
            int digitneedtodelete = 0;
            for(int i =0;i<newSize;i++)
            {
                if(passedfirst)
                    break;
                if(tempValue[i] == 0)
                {
                    if(tempValue[i+1] == '.')
                    {
                        passedfirst = true;
                        break;
                    }
                    else if(tempValue[i+1] != '0')
                    {
                        passedfirst = true;
                    }
                    digitneedtodelete++;
                }
            }

            char* returnValue = new char[newSize+2-digitneedtodelete];
            returnValue[0] = '-';
            returnValue[newSize+1-digitneedtodelete] = '\0';
            for(int i=digitneedtodelete; i<newSize;i++)
            {
                returnValue[i+1-digitneedtodelete] = tempValue[i];
            }
            Decimal returnObj(returnValue);
            delete[] tempValue;
            delete[] returnValue;
            return returnObj;
        
        }
        else if(another.isLargerThan(copyThis))
        {
            if(digitAfterForAnother == digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal;i-- )
                {
                    int temp = charToNumber(another.content[another.size-1+(i-newSize+1)]) - charToNumber(copyThis.content[copyThis.size-1+(i-newSize+1)])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    else if(!passedlast&&temp == 0)
                    {
                        tempValue[i] = '\0';
                        continue;
                    }

                    tempValue[i] = numberToChar(temp);
                    passedlast = true;
                }
            }
            else if(digitAfterForAnother>digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForThis;i--)
                {
                    tempValue[i] = another.content[another.size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForThis; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(another.content[another.size-1+(i-newSize+1)]) - charToNumber(copyThis.content[copyThis.size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                }
            }
            else if(digitAfterForThis>digitAfterForAnother)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForAnother;i--)
                {
                    tempValue[i] = copyThis.content[copyThis.size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForAnother; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(another.content[another.size-1+(i-newSize+1)]) - charToNumber(copyThis.content[copyThis.size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                    
                }
            }
            tempValue[indexOfDecimal] = '.';

            if(digitBeforeForAnother == digitBeforeForThis)
            {
                for(int i=indexOfDecimal-1;i>=0;i--)
                {
                    int temp = charToNumber(another.content[i])-charToNumber(copyThis.content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }
            else
            {
                int gap = digitBeforeForThis-digitBeforeForAnother;
                for(int i=indexOfDecimal-1;i>indexOfDecimal-1-digitBeforeForAnother;i--)
                {
                    int temp = charToNumber(another.content[i]) - charToNumber(copyThis.content[i-gap])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }

                for(int i=indexOfDecimal-1-digitBeforeForAnother;i>=0;i--)
                {
                    int temp = charToNumber(another.content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }

            bool passedfirst = false;
            int digitneedtodelete = 0;
            for(int i =0;i<newSize;i++)
            {
                if(passedfirst)
                    break;
                if(tempValue[i] == 0)
                {
                    if(tempValue[i+1] == '.')
                    {
                        passedfirst = true;
                        break;
                    }
                    else if(tempValue[i+1] != '0')
                    {
                        passedfirst = true;
                    }
                    digitneedtodelete++;
                }
            }

            char* returnValue = new char[newSize+1-digitneedtodelete];
            returnValue[newSize-digitneedtodelete] = '\0';
            for(int i=digitneedtodelete; i<newSize;i++)
            {
                returnValue[i-digitneedtodelete] = tempValue[i];
            }
            Decimal returnObj(returnValue);
            delete[] tempValue;
            delete[] returnValue;
            return returnObj;
        }
        else
        {
            return Decimal(0);
        }
    }
    else
    {
        if(another.isNegative())
            return  add(another.flipSign());

        int needToDelete = 0;
        bool passedlast = false;
        int digitBeforeForThis = countDigitsBeforeDP();
        int digitAfterForThis = countDigitsAfterDP();
        int digitBeforeForAnother = another.countDigitsBeforeDP();
        int digitAfterForAnother = another.countDigitsAfterDP();

        int indexOfDecimal = (digitBeforeForAnother>=digitBeforeForThis)?digitBeforeForAnother:digitBeforeForThis;

        bool nodecimal = !(digitAfterForAnother||digitAfterForThis);

        int newSize = ((digitBeforeForAnother>=digitBeforeForThis)?digitBeforeForAnother:digitBeforeForThis)+
                        ((digitAfterForAnother>=digitAfterForThis)?digitAfterForAnother:digitAfterForThis)+1;
        if(nodecimal)
            newSize--;

        char* tempValue = new char[newSize];

        if(isLargerThan(another))
        {
            if(digitAfterForAnother == digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal;i-- )
                {
                    int temp = charToNumber(content[size-1+(i-newSize+1)]) - charToNumber(another.content[another.size-1+(i-newSize+1)])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    else if(!passedlast&&temp == 0)
                    {
                        tempValue[i] = '\0';
                        continue;
                    }

                    tempValue[i] = numberToChar(temp);
                    passedlast = true;
                }
            }
            else if(digitAfterForAnother>digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForThis;i--)
                {
                    tempValue[i] = another.content[another.size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForThis; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) - charToNumber(another.content[another.size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                }
            }
            else if(digitAfterForThis>digitAfterForAnother)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForAnother;i--)
                {
                    tempValue[i] = content[size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForAnother; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(content[size-1+(i-newSize+1)]) - charToNumber(another.content[another.size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                    
                }
            }
            tempValue[indexOfDecimal] = '.';

            if(digitBeforeForAnother == digitBeforeForThis)
            {
                for(int i=indexOfDecimal-1;i>=0;i--)
                {
                    int temp = charToNumber(content[i])-charToNumber(another.content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }
            else
            {
                int gap = digitBeforeForThis-digitBeforeForAnother;
                for(int i=indexOfDecimal-1;i>indexOfDecimal-1-digitBeforeForAnother;i--)
                {
                    int temp = charToNumber(content[i]) - charToNumber(another.content[i-gap])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }

                for(int i=indexOfDecimal-1-digitBeforeForAnother;i>=0;i--)
                {
                    int temp = charToNumber(content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }

            bool passedfirst = false;
            int digitneedtodelete = 0;
            for(int i =0;i<newSize;i++)
            {
                if(passedfirst)
                    break;
                if(tempValue[i] == 0)
                {
                    if(tempValue[i+1] == '.')
                    {
                        passedfirst = true;
                        break;
                    }
                    else if(tempValue[i+1] != '0')
                    {
                        passedfirst = true;
                    }
                    digitneedtodelete++;
                }
            }

            char* returnValue = new char[newSize+1-digitneedtodelete];
            returnValue[newSize-digitneedtodelete] = '\0';
            for(int i=digitneedtodelete; i<newSize;i++)
            {
                returnValue[i-digitneedtodelete] = tempValue[i];
            }
            Decimal returnObj(returnValue);
            delete[] tempValue;
            delete[] returnValue;
            return returnObj;
        
        }
        else if(another.isLargerThan(*this))
        {
            if(digitAfterForAnother == digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal;i-- )
                {
                    int temp = charToNumber(another.content[another.size-1+(i-newSize+1)]) - charToNumber(content[size-1+(i-newSize+1)])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    else if(!passedlast&&temp == 0)
                    {
                        tempValue[i] = '\0';
                        continue;
                    }

                    tempValue[i] = numberToChar(temp);
                    passedlast = true;
                }
            }
            else if(digitAfterForAnother>digitAfterForThis)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForThis;i--)
                {
                    tempValue[i] = another.content[another.size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForThis; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(another.content[another.size-1+(i-newSize+1)]) - charToNumber(content[size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                }
            }
            else if(digitAfterForThis>digitAfterForAnother)
            {
                for(int i = newSize-1; i>indexOfDecimal+digitAfterForAnother;i--)
                {
                    tempValue[i] = content[size-1+(i-newSize+1)];
                }
                for(int i = indexOfDecimal+digitAfterForAnother; i>indexOfDecimal;i--)
                {
                        int temp = charToNumber(another.content[another.size-1+(i-newSize+1)]) - charToNumber(content[size-1+(i-newSize+1)])+needToDelete;
                        needToDelete = 0;
                        if(temp<0)
                        {
                            needToDelete = -1;
                            temp += 10;
                        }

                        tempValue[i] = numberToChar(temp);
                    
                }
            }
            tempValue[indexOfDecimal] = '.';

            if(digitBeforeForAnother == digitBeforeForThis)
            {
                for(int i=indexOfDecimal-1;i>=0;i--)
                {
                    int temp = charToNumber(another.content[i])-charToNumber(content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }
            else
            {
                int gap = digitBeforeForThis-digitBeforeForAnother;
                for(int i=indexOfDecimal-1;i>indexOfDecimal-1-digitBeforeForAnother;i--)
                {
                    int temp = charToNumber(another.content[i]) - charToNumber(content[i-gap])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }

                for(int i=indexOfDecimal-1-digitBeforeForAnother;i>=0;i--)
                {
                    int temp = charToNumber(another.content[i])+needToDelete;
                    needToDelete = 0;
                    if(temp<0)
                    {
                        needToDelete = -1;
                        temp += 10;
                    }
                    tempValue[i] = numberToChar(temp);
                }
            }

            bool passedfirst = false;
            int digitneedtodelete = 0;
            for(int i =0;i<newSize;i++)
            {
                if(passedfirst)
                    break;
                if(tempValue[i] == 0)
                {
                    if(tempValue[i+1] == '.')
                    {
                        passedfirst = true;
                        break;
                    }
                    else if(tempValue[i+1] != '0')
                    {
                        passedfirst = true;
                    }
                    digitneedtodelete++;
                }
            }


            char* returnValue = new char[newSize+2-digitneedtodelete];
            returnValue[0] = '-';
            returnValue[newSize+1-digitneedtodelete] = '\0';
            for(int i=digitneedtodelete; i<newSize;i++)
            {
                returnValue[i+1-digitneedtodelete] = tempValue[i];
            }
            Decimal returnObj(returnValue);
            delete[] tempValue;
            delete[] returnValue;
            return returnObj;
        }
        else
        {
            return Decimal(0);
        }
    }
}


int Decimal::countDigitsBeforeDP() const
{
    int digits = 0;
    for(int i = 0; i<size; i++)
    {
        if(content[i] == '.')
            break;
        digits++;
    }
    if(isNegative())
        digits--;
    return digits;
}

int Decimal::countDigitsAfterDP() const
{
    int digitbefore = countDigitsBeforeDP();
    if(isNegative())
    {
        if(size-digitbefore!=1)
            return size-2-digitbefore;
        else
            return 0;
    }
        
    if(size-digitbefore !=0)
        return size-1-countDigitsBeforeDP();
    return 0;
}

