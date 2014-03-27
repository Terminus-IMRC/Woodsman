#include "common.h"
#include "string_utils.h"

int count_number_of_elements_in_string(char *str);

int count_number_of_elements_in_string(char *str)
{
        int res=0;
        _Bool if_prior_digit=0;

        do{
                if(isdigit((int)*str)){
                        if(!if_prior_digit)
                                res++;
                        if_prior_digit=1;
                }else
                        if_prior_digit=0;
        }while(*++str);

        return res;
}
