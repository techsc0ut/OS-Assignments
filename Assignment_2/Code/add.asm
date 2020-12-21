section .data                             
						;here we can declare variables which will be further used in our prgram.
			
			CurrentDigit db 1      ;It will it be used as a free space which will be used further to print the characters one by one in the final printing routine.
			nextLine: db "",10     ;Here 10 refers to '\n' or LF character which will be last printed.


section .text                 		  
								
					  	;here our main instructions are performed.
			
			global Add       	;Here Add is a Label where it will jump in the control flow for fetching further instructions.

			mov rax,60	  	;This is the structure for calling System_exit Call, where the ID is Pre-defined as 60.	  	
			mov rdi,0        	;0 conveys successful execution with no errors.				
	    		syscall
	    		ret	
	    								
	    								

Add:
			
			mov r8,0         	;Initializing Register R9 to zero , it will help us to note if the number is +ve or -ve.
			push 10	  	;Pushing 10 in the System Stack so that to determine at last , we have reached the end , and will thus print the new next line.

			add rdi,rsi 	 	;By default the first argument passed to the Assembly code is stored in rdi , whereas second in rsi , Since these are the 2 values 

			                 	;to be added , we have used the math function add for the task , which will store the result in rdi itself.
			mov rax,rdi      	;Copied the result in the rax register. 
			cmp rax,0
			jge Loop1        	;Here we check if the value stored in rax register (result of addition) is +ve , then immediately jump tp the Label 'Loop1' in the 
			                 	;                                                                                                                          Program.
			mov r10,-1       	;Else we will make it positive , by multiplying it by -1 ,to do so we will first store -1 in register R10 , then multiply it with  
						;value of rax register .
			mul r10          	;The mul function automatically multiplies the value stored in the rax register with the passed value i.e r10 in our case .
			mov r8,1         	;Noting that the result is -ve.


Loop1:                       		  	;In this Label we have defined a loop that will take the resultant number and push the ASCII values of all the digits one by one in 
					  	;System stack in backward Fashion . To do so we will divide the value stored in rax (result initially) by 10, and store the answer 
				          	;in rax and the remainder in rdx using div function , and will continue until we get 0 in rax .

			mov rdx,0	  	;Each time assigning 0 initially to rdx . 
			mov rbx,10       	;rbx to 10 , inorder to divide the rax with 10.
			div rbx          	;function will store answer in rax and remainder in rdx.
			call getAscii    	;Calculate Ascii value for each digit by adding 48 , since 0 start with 48 then increment for subsequently digits. 
			push rdx         	;storing in rdx.
			cmp rax,0        	;checking if the lastdigit (first actually) is reached or not.
			jne Loop1        	;if No then continue .
			cmp r8,0         	;checking if the resultant addition was +ve or -ve , since we had to push the ascii of '-' character in last , So as to print the 
			                 	;the same first.
			je printingDigit 	;if it was +ve , then directly approach the printing function .  
			jmp pushNegSign  	;otherwise push ascii of '-' character to system stack by jumping to following label function.


getAscii:

			add rdx,48            	;Provding Ascii value corresponding to the digit , keeping in mind that it starts from 48 for 0 and then increment subsequently.
			ret        


pushNegSign:

			push 45          	;Ascii corresponding to '-' pushed to stack. 


printingDigit:


			pop r9                ;Popping Out the uppermost digit one by one which is actually the endmost digit in sequence , and storing it in R9 register.
			mov [CurrentDigit],r9 ;This will enable the Variable CurrentDigit point to value in R9.
			call writeCharacter        ;System Call to Write the current popped character. 
			cmp r9,10             ;check whether Most Significant digit printed or not.
			jne printingDigit     ;Continue otherwise.
			
			mov rax,1    		  ;System call to print new Line character to approach a new line .
			mov rdi,1             ;Here (rax) ID is 1, here 1 next to rdi conveys standard output role , and rsi points to the address of the character to be  
			mov rsi,nextLine      ;printed and value next to rdx stands for length of the character or string. 
			mov rdx,0
			syscall 
			ret 
			




writeCharacter:
			mov rax,1            ;Here We are printing the current digit with the help of write System call , where ID is predefined as 1 , Moreover 1 next to rdi specifying STDOUT 
					      ;Operation and rsi points to address of CurrentDigit and rdx has been assigned 1 next to it for the length of the character .		
			mov rdi,1
			mov rsi,CurrentDigit
			mov rdx,1
			syscall
			ret
