void
itoa(int val, char *buf, unsigned radix)
{
    char *p;             
    char *firstdig;      
    char temp;           
    unsigned digval;     
    p = buf;
    if(val < 0)
    {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }
    firstdig = p; 
    do{
        digval = (unsigned)(val % radix);
        val /= radix;
       
        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a'); 
        else
            *p++ = (char)(digval + '0');      
    } while(val);
   
    *p-- = '\0';         
    do{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;        
    } while(firstdig < p);  
}

