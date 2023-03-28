#include <stdio.h>

#define MAX_EXPRESSION_LENGTH 100

double getANumber(char *str){
    double result = 0.0;
    int decimal_place = -1;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            int digit_value = str[i] - '0';
            if (decimal_place >= 0) {
                result += digit_value / (10.0 * decimal_place);
                decimal_place *= 10;
            } else {
                result *= 10.0;
                result += digit_value;
            }
        } else if (str[i] == '.') {
            decimal_place = 1;
        } else {
            return result;
        }
        i++;
    }
    return result;
}

double addAndSub(char *q){
    int unary_minus=0, in_number=0;
    double sum=0;
    char operator='\0';
    if(*q=='-'){
        unary_minus=1;
        q++;
    }
    while(*q!='\0'){
        if(((*q<='9' && *q>='0') || *q=='.') && in_number==0 && operator=='\0'){
            in_number=1;
            sum = sum + getANumber(q);
            if(unary_minus==1){
                sum=sum*(-1);
            }
        } else if(((*q<='9' && *q>='0') || *q=='.') && in_number==1){
        }else if(*q=='+'){
            in_number=0;
            operator='+';
        }else if(*q=='-'){
            in_number=0;
            operator='-';
        }else if(((*q<='9' && *q>='0') || *q=='.') && in_number==0 && (operator=='+' || operator=='-')){
            unary_minus=0;
            in_number=1;
            if(operator=='+'){
                sum=sum+getANumber(q);
            }else if(operator=='-'){
                sum=sum-getANumber(q);
            }
        }else if(((*q<='9' && *q>='0') || *q=='.') && in_number==1 && (operator=='+' || operator=='-')){
        }
        q++;
    }
    return sum;
}


double realCalculation(char *q, char *p){
    double result=0, operand=0;
    char *start=q, *help_start=q, *help_end, *remember=q, operator='\0';
    int unary_minus=0, in_number=0, calculation_made=0, result_has_value=0;

    if(*q=='-'){
        unary_minus=1;
        q++;
    }

    while(*q!='\0' && *q!=')'){
        if(((*q<='9' && *q>='0') || *q=='.') && in_number==0 && operator=='\0'){
            in_number=1;
            help_start=q;
            remember=help_start;
            operand = getANumber(q);
            if(unary_minus==1){
                operand=operand*(-1);
            }
        }else if(((*q<='9' && *q>='0') || *q=='.') && in_number==1 && operator=='\0'){
        }else if(*q=='*'){
            in_number=0;
            operator='*';
        }else if(*q=='/'){
            in_number=0;
            operator='/';
        }else if(((*q<='9' && *q>='0') || *q=='.') && in_number==0 && (operator=='*' || operator=='/')){
            unary_minus=0;
            calculation_made=1;
            in_number=1;
            if(result_has_value){
                if(operator=='*'){
                    result=result*getANumber(q);
                }else if(operator=='/'){
                    result=result/getANumber(q);
                }
            }else {
                if(operator=='*'){
                    result=operand*getANumber(q);
                }else if(operator=='/'){
                    result=operand/getANumber(q);
                }
            }
            char *ll= q;
            while((*ll >='0' && *ll<='9') || *ll=='.'){
                ll++;
            }
            if(*ll=='\0'){
                char new[100];
                sprintf(new,"%g", result);
                char *pp=new;
                while(*pp!='\0'){
                    *help_start=*pp;
                    help_start++;
                    pp++;
                }
                if(*help_start=='\0'){
                    break;
                }
                *help_start='\0';
                q=remember;
                help_start=q;
                help_end=q;
                operand=result;
                in_number=0;
                operator='\0';
                unary_minus=0;
            }
            result_has_value=1;
        }else if(((*q<='9' && *q>='0') || *q=='.') && in_number==1 && (operator=='*' || operator=='/')){

        }else if (calculation_made==1 && in_number==1 && operator!='\0'){
            result_has_value=0;
            in_number=0;
            help_end=q;
            char new[100];
            sprintf(new,"%g", result);
            char *pp=new;
            while(*pp!='\0'){
                *help_start=*pp;
                help_start++;
                pp++;
            }
            while(*help_end!='\0'){
                *help_start=*help_end;
                help_start++;
                help_end++;
            }
            if(*help_start=='\0'){
                break;
            }
            *help_start='\0';
            q=remember;
            help_start=q;
            help_end=q;
            operand=result;
            in_number=0;
            operator='\0';
            unary_minus=0;
        } else {
            unary_minus=0;
            in_number=0;
            operator='\0';
        }
        q++;
    }
    return addAndSub(start);
}

int has_brackets(char *s){
    while(*s!='\0'){
        if(*s=='('){
            return 1;
        }
        s++;
    }
    return 0;
}

double calculate(char *str){
    char *p = str, *q = str, *start=str, *begin=str;
    int in_brackets=0;
    double result=0;

    while(*p!='\0'){
        if(*p=='('){
            in_brackets=1;
        }else if(*p==')' && in_brackets==1){
            char *t=p;
            while(*t!='('){
                t--;
            }
            q=t;
            result = calculate((q+1));
                char new[100];
                sprintf(new,"%g", result);
                char *pp=new;
                char *help_start=q;
                char *help_end=p;
                while(*pp!='\0'){
                    *help_start=*pp;
                    help_start++;
                    pp++;
                }
                help_end++;
                while(*help_end!='\0'){
                    *help_start=*help_end;
                    help_start++;
                    help_end++;
                }
                if(*help_start=='\0'){
                    break;
                }
                *help_start='\0';
                start=str;
                if(!has_brackets(start)){
                    in_brackets=0;
                }
            }
            p++;
    }
    p=begin;
    q=begin;
    if(in_brackets==0){
        while(*p!='\0'){
            p++;
        }
        result= realCalculation(q,p);
    }
   return result;
}

int good_entry(char *p){
    int first_char=1, prev_digit=0, prev_open_bracket=0, prev_operator=0,
    num_of_opening=0, num_of_closing=0, prev_close_bracket=0, unary_minus=0;
    if(*p=='-'){
        unary_minus=1;
    }
    char *begin=p;
    while(*p!='\0'){
        if(((*p>='0' && *p<='9') || *p=='.') && (first_char || prev_operator || prev_open_bracket || prev_digit)){
            first_char=0;
            prev_digit=1;
            prev_operator=0;
            prev_open_bracket=0;
            prev_close_bracket=0;
        }else if((*p=='+' || *p=='-' || *p=='*' || *p=='/') && (prev_close_bracket || prev_digit || prev_open_bracket || unary_minus)){
            if(*(p+1)=='+' || *(p+1)=='-' || *(p+1)=='*' || *(p+1)=='/'){
                return 0;
            }
            prev_operator=1;
            prev_close_bracket=0;
            prev_digit=0;
            prev_open_bracket=0;
        }else if(*p=='(' && (first_char || prev_operator)){
            first_char=0;
            prev_operator=0;
            prev_open_bracket=1;
            prev_close_bracket=0;
            prev_digit=0;
            num_of_opening++;
        }else if(*p==')' && prev_digit){
            prev_close_bracket=1;
            num_of_closing++;
            prev_operator=0;
            prev_open_bracket=0;
            prev_digit=0;
        }else {
            return 0;
        }
        p++;
    }
    if(prev_operator || prev_open_bracket || num_of_closing!=num_of_opening) return 0;
    return 1;
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH];
    printf("Okaaaaay, lets go...\n");
    char c;
    int counter=0;
    while((c=getchar())!='\n' && counter<MAX_EXPRESSION_LENGTH){
        expression[counter++]=c;
    }
    expression[counter]='\0';

    // Remove newline character from input
    int i = 0;
    while (expression[i] != '\0') {
        if (expression[i] == '\n') {
            expression[i] = '\0';
            break;
        }
        i++;
    }
    // add null character at end of input string
    // Evaluate expression and print result
    if(!good_entry(expression)){
        printf("nop!");
        return 0;
    }
    double result = calculate(expression);
    printf("%.2f", result);
    char final[100];
    sprintf(final,"%f", result);
    i=0;
    while(final[i]!='\0' && final[i]!='.'){
        i++;
    }
    if(final[i]=='.'){
        i++;
        i++;
        i++;
    }
    printf("\n");
    for(int j=0; j<i; j++){
        printf("=");
    }
    return 0;
}
