#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct OPCODES {			// optab implementation
	char mneumonic[10];
	int format;
	int hexCode;
};
struct OPCODES opcodes[60];		

struct SYMTAB{				// symtab implementation
    char symbol[10];
    int addr;
    };
struct SYMTAB symtab[50];

int startAddr,LOCCTR,symbolCount = 0,length, flag=0, address[1000]; 
char line[20],label[10],opcode[10],operand[10],programName[10],operandHex[10],operandIndex[10]={'\0'};

void writeOpcodeSheet(void) {		// optab initialization
	
	strcpy(opcodes[0].mneumonic, "ADD");                       // 1. ADD
	opcodes[0].format = 3;
	opcodes[0].hexCode = 0x18;

	strcpy(opcodes[1].mneumonic, "ADDF");                      // 2. ADDF
	opcodes[1].format = 3;
	opcodes[1].hexCode = 0x58;

	strcpy(opcodes[2].mneumonic, "ADDR");                      // 3. ADDR
	opcodes[2].format = 2;
	opcodes[2].hexCode = 0x90;	

	strcpy(opcodes[3].mneumonic, "AND");                       // 4. AND
	opcodes[3].format = 3;
	opcodes[3].hexCode = 0x40;
	
	strcpy(opcodes[4].mneumonic, "CLEAR");                     // 5. CLEAR
	opcodes[4].format = 2;
	opcodes[4].hexCode = 0xB4;

	strcpy(opcodes[5].mneumonic, "COMP");                      // 6. COMP
	opcodes[5].format = 3;
	opcodes[5].hexCode = 0x28;

	strcpy(opcodes[6].mneumonic, "COMPF");                     // 7. COMPF
	opcodes[6].format = 3;
	opcodes[6].hexCode = 0x88;

	strcpy(opcodes[7].mneumonic, "COMPR");                     // 8. COMPR
	opcodes[7].format = 2;
	opcodes[7].hexCode = 0xA0;

	strcpy(opcodes[8].mneumonic, "DIV");                       // 9. DIV
	opcodes[8].format = 3;
	opcodes[8].hexCode = 0x24;

	strcpy(opcodes[9].mneumonic, "DIVF");                      // 10. DIVF
	opcodes[9].format = 3;
	opcodes[9].hexCode = 0x64;

	strcpy(opcodes[10].mneumonic, "DIVR");                     // 11. DIVR
	opcodes[10].format = 2;
	opcodes[10].hexCode = 0x9C;

	strcpy(opcodes[11].mneumonic, "FIX");                      // 12. FIX
	opcodes[11].format = 1;
	opcodes[11].hexCode = 0xC4;

	strcpy(opcodes[12].mneumonic, "FLOAT");                    // 13. FLOAT
	opcodes[12].format = 1;
	opcodes[12].hexCode = 0xC0;

	strcpy(opcodes[13].mneumonic, "HIO");                      // 14. HIO
	opcodes[13].format = 1;
	opcodes[13].hexCode = 0xF4;

	strcpy(opcodes[14].mneumonic, "J");                        // 15. J
	opcodes[14].format = 3;
	opcodes[14].hexCode = 0x3C;

	strcpy(opcodes[15].mneumonic, "JEQ");                      // 16. JEQ
	opcodes[15].format = 3;
	opcodes[15].hexCode = 0x30;

	strcpy(opcodes[16].mneumonic, "JGT");                      // 17. JGT
	opcodes[16].format = 3;
	opcodes[16].hexCode = 0x34;

	strcpy(opcodes[17].mneumonic, "JLT");                      // 18. JLT
	opcodes[17].format = 3;
	opcodes[17].hexCode = 0x38;

	strcpy(opcodes[18].mneumonic, "JSUB");                     // 19. JSUB
	opcodes[18].format = 3;
	opcodes[18].hexCode = 0x48;

	strcpy(opcodes[19].mneumonic, "LDA");                      // 20. LDA
	opcodes[19].format = 3;
	opcodes[19].hexCode = 0x00;

	strcpy(opcodes[20].mneumonic, "LDB");                      // 21. LDB
	opcodes[20].format = 3;
	opcodes[20].hexCode = 0x68;

	strcpy(opcodes[21].mneumonic, "LDCH");                     // 22. LDCH
	opcodes[21].format = 3;
	opcodes[21].hexCode = 0x50;
	
	strcpy(opcodes[22].mneumonic, "LDF");                      // 23. LDF
	opcodes[22].format = 3;
	opcodes[22].hexCode = 0x70;
	
	strcpy(opcodes[23].mneumonic, "LDL");                      // 24. LDL
	opcodes[23].format = 3;
	opcodes[23].hexCode = 0x08;
	
	strcpy(opcodes[24].mneumonic, "LDS");                      // 25. LDS
	opcodes[24].format = 3;
	opcodes[24].hexCode = 0x6C;
	
	strcpy(opcodes[25].mneumonic, "LDT");                      // 26. LDT
	opcodes[25].format = 3;
	opcodes[25].hexCode = 0x74;
	
	strcpy(opcodes[26].mneumonic, "LDX");                      // 27. LDX
	opcodes[26].format = 3;
	opcodes[26].hexCode = 0x04;
	
	strcpy(opcodes[27].mneumonic, "LPS");                      // 28. LPS
	opcodes[27].format = 3;
	opcodes[27].hexCode = 0xD0;
	
	strcpy(opcodes[28].mneumonic, "MUL");                      // 29. MUL
	opcodes[28].format = 3;
	opcodes[28].hexCode = 0x20;
	
	strcpy(opcodes[29].mneumonic, "MULF");                     // 30. MULF
	opcodes[29].format = 3;
	opcodes[29].hexCode = 0x60;
	
	strcpy(opcodes[30].mneumonic, "MULR");                     // 31. MULR
	opcodes[30].format = 2;
	opcodes[30].hexCode = 0x98;
	
	strcpy(opcodes[31].mneumonic, "NORM");                     // 32. NORM
	opcodes[31].format = 1;
	opcodes[31].hexCode = 0xC8;
	
	strcpy(opcodes[32].mneumonic, "OR");                       // 33. OR
	opcodes[32].format = 3;
	opcodes[32].hexCode = 0x44;
	
	strcpy(opcodes[33].mneumonic, "RD");                       // 34. RD
	opcodes[33].format = 3;
	opcodes[33].hexCode = 0xD8;
	
	strcpy(opcodes[34].mneumonic, "RMO");                      // 35. RMO
	opcodes[34].format = 2;
	opcodes[34].hexCode = 0xAC;
	
	strcpy(opcodes[35].mneumonic, "RSUB");                     // 36. RSUB
	opcodes[35].format = 3;
	opcodes[35].hexCode = 0x4C;
	
	strcpy(opcodes[36].mneumonic, "SHIFTL");                   // 37. SHIFTL
	opcodes[36].format = 2;
	opcodes[36].hexCode = 0xA4;
	
	strcpy(opcodes[37].mneumonic, "SHIFTR");                   // 38. SHIFTR
	opcodes[37].format = 2;
	opcodes[37].hexCode = 0xA8;
	
	strcpy(opcodes[38].mneumonic, "SIO");                      // 39. SIO
	opcodes[38].format = 1;
	opcodes[38].hexCode = 0xF0;
	
	strcpy(opcodes[39].mneumonic, "SSK");                      // 40. SSK
	opcodes[39].format = 3;
	opcodes[39].hexCode = 0xEC;
	
	strcpy(opcodes[40].mneumonic, "STA");                      // 41. STA
	opcodes[40].format = 3;
	opcodes[40].hexCode = 0x0C;
	
	strcpy(opcodes[41].mneumonic, "STB");                      // 42. STB
	opcodes[41].format = 3;
	opcodes[41].hexCode = 0x78;
	
	strcpy(opcodes[42].mneumonic, "STCH");                     // 43. STCH
	opcodes[42].format = 3;
	opcodes[42].hexCode = 0x54;
	
	strcpy(opcodes[43].mneumonic, "STF");                      // 44. STF
	opcodes[43].format = 3;
	opcodes[43].hexCode = 0x80;
	
	strcpy(opcodes[44].mneumonic, "STI");                      // 45. STI
	opcodes[44].format = 3;
	opcodes[44].hexCode = 0xD4;
	
	strcpy(opcodes[45].mneumonic, "STL");                      // 46. STL
	opcodes[45].format = 3;
	opcodes[45].hexCode = 0x14;
	
	strcpy(opcodes[46].mneumonic, "STS");                      // 47. STS
	opcodes[46].format = 3;
	opcodes[46].hexCode = 0x7C;
	
	strcpy(opcodes[47].mneumonic, "STSW");                     // 48. STSW
	opcodes[47].format = 3;
	opcodes[47].hexCode = 0xE8;
	
	strcpy(opcodes[48].mneumonic, "STT");                      // 49. STT
	opcodes[48].format = 3;
	opcodes[48].hexCode = 0x84;
	
	strcpy(opcodes[49].mneumonic, "STX");                      // 50. STX
	opcodes[49].format = 3;
	opcodes[49].hexCode = 0x10;
	
	strcpy(opcodes[50].mneumonic, "SUB");                      // 51. SUB
	opcodes[50].format = 3;
	opcodes[50].hexCode = 0x1C;
	
	strcpy(opcodes[51].mneumonic, "SUBF");                     // 52. SUBF
	opcodes[51].format = 3;
	opcodes[51].hexCode = 0x5C;
	
	strcpy(opcodes[52].mneumonic, "SUBR");                     // 53. SUBR
	opcodes[52].format = 2;
	opcodes[52].hexCode = 0x94;
	
	strcpy(opcodes[53].mneumonic, "SVC");                      // 54. SVC
	opcodes[53].format = 2;
	opcodes[53].hexCode = 0xB0;
	
	strcpy(opcodes[54].mneumonic, "TD");                       // 55. TD
	opcodes[54].format = 3;
	opcodes[54].hexCode = 0xE0;
	
	strcpy(opcodes[55].mneumonic, "TIO");                      // 56. TIO
	opcodes[55].format = 1;
	opcodes[55].hexCode = 0xF8;
	
	strcpy(opcodes[56].mneumonic, "TIX");                      // 57. TIX
	opcodes[56].format = 3;
	opcodes[56].hexCode = 0x2C;
	
	strcpy(opcodes[57].mneumonic, "TIXR");                     // 58. TIXR
	opcodes[57].format = 2;
	opcodes[57].hexCode = 0xB8;
	
	strcpy(opcodes[58].mneumonic, "WD");                       // 59. WD
	opcodes[58].format = 3;
	opcodes[58].hexCode = 0xDC;

}


int getFormat (char *str) {		// function returns format of an opcode; returns -1 in case of unrecognized opcode

	int start, end, i;
	switch (str[0]) {
		case 'A':
			start = 0;
			end =3;
			break;

		
		case 'C':
			start = 4;
			end = 7;
			break;

		case 'D':
			start = 8;
			end = 10;
			break;

		case 'F':
			start = 11;
			end = 12;
			break;

		case 'H':
			start = 13;
			end = 13;
			break;
		
		case 'J':
			start = 14;
			end = 18;
			break;
		
		case 'L':
			start = 19;
			end = 27;
			break;

		case 'M':
			start = 28;
			end = 30;
			break;
		
		case 'N':
			start = 31;
			end = 31;
			break;

		case 'O':
			start = 32;
			end = 32;
			break;

		case 'R':
			start = 33;
			end = 35;
			break;

		case 'S':
			start = 36;
			end = 53;
			break;

		case 'T':
			start = 54;
			end = 57;
			break;

		case 'W':
			start = 58;
			end = 58;
			break;

		case '+':
			return 4;
			break;
		
		default:
			return -1;
	
		}

	for (i=start; i<=end; i++) {
		if(!strcmp(str, opcodes[i].mneumonic))
			return opcodes[i].format;
		}
	
	return -1;

}


int getHexCode (char *str) {		// function returns hexadecimal equivalent of an opcode; returns -1 incase of unrecognized opcode
	
	int size, i=1, j=0, start=0, end=0;	 

	switch (str[0]) {
		case 'A':
			start = 0;
			end =3;
			break;

		
		case 'C':
			start = 4;
			end = 7;
			break;

		case 'D':
			start = 8;
			end = 10;
			break;

		case 'F':
			start = 11;
			end = 12;
			break;

		case 'H':
			start = 13;
			end = 13;
			break;
		
		case 'J':
			start = 14;
			end = 18;
			break;
		
		case 'L':
			start = 19;
			end = 27;
			break;

		case 'M':
			start = 28;
			end = 30;
			break;
		
		case 'N':
			start = 31;
			end = 31;
			break;

		case 'O':
			start = 32;
			end = 32;
			break;

		case 'R':
			start = 33;
			end = 35;
			break;

		case 'S':
			start = 36;
			end = 53;
			break;

		case 'T':
			start = 54;
			end = 57;
			break;
		
		case 'W':
			start = 58;
			end = 58;
			break;
		
		default:
			return -1;
	
		}

	for (i=start; i<=end; i++) {
		if(!strcmp(str, opcodes[i].mneumonic))
			return opcodes[i].hexCode;
		}
	
	return -1;
	
}

void readLine(void) {		// function reads one line of input file at a time; 
				// segregates the parts of the line into label, opcode and operand
	char buffer[10],wordA[10],wordB[10],wordC[10];
	int i,j = 0,count = 0;
 	label[0]=opcode[0]=operand[0]=wordA[0]=wordB[0]=wordC[0]='\0';
 	for(i=0;line[i]!='\0';i++) {
  		if(line[i]!=' ')
  			buffer[j++]=line[i];
  		else {
  			buffer[j]='\0';
  			strcpy(wordC,wordB);
  			strcpy(wordB,wordA);
  			strcpy(wordA,buffer);
  			j=0;
  			count++;
  		     }
  	}
  	buffer[j-1]='\0';
  	strcpy(wordC,wordB);
  	strcpy(wordB,wordA);
  	strcpy(wordA,buffer);
  	switch(count) {
  		case 0:
			strcpy(opcode,wordA);
  			break;
  		case 1:
			strcpy(opcode,wordB);
			strcpy(operand,wordA);
  			break;
  		case 2:	
			strcpy(label,wordC);
			strcpy(opcode,wordB);
			strcpy(operand,wordA);
  			break;
  		}
}

void checkLabel(void) {			// function checks if the label is present in the symtab or not
	int k,duplicateSymbol=0;
   	for(k=0; k<symbolCount; k++)
   		if(!strcmp(label,symtab[k].symbol)) {
      			symtab[k].addr=-1;
      			duplicateSymbol=1;		// duplicate symbol detected
			printf("\n\nERROR: %s has already been defined\n",label);
			flag=1;	
      			break;
      		}
      	if(!duplicateSymbol) {
      		strcpy(symtab[symbolCount].symbol,label);
      		symtab[symbolCount++].addr=LOCCTR;
      	}
}


void checkOpcode(void) {		// function checks for opcodes and increments the LOCCTR accordingly
	int k=0,found=0, addrLength;
   	addrLength = getFormat(opcode); 
   	if(addrLength!= -1) {
		LOCCTR+= addrLength;
		found = 1;
	}	   
      	if(!found) {
         	if(!strcmp(opcode,"WORD")) 
			LOCCTR+=3;
         	else if (!strcmp(opcode,"RESW"))
			LOCCTR+= (3*atoi(operand));
         	else if(!strcmp(opcode,"RESB"))
			LOCCTR+=atoi(operand);
        }
}

int isAssemblerDirective(char *str) {		// function checks if opcode is an assembler directive
	if(!strcmp(str, "RESB"))
		return 0;
	
	else if(!strcmp(str, "WORD"))
		return 0;

	else if(!strcmp(str, "RESW"))
		return 0;

	else if(!strcmp(str, "BYTE"))
		return 0;
	
	else 
		return -1;
	
}

int isIndexed(char *str) {		// function checks for indexed addressing mode
	int i=0, flag=0;
	char buff[20]={'\0'};
	for(i=0;str[i]!='\0';i++) {
		if(str[i] == ',')
			flag = 1;
	}
	
	if(flag == 1) {
		i=0;
		while(str[i] != ',')
 			buff[i++] = str[i];
	}  
	buff[i]='\0';
	strcpy(operandIndex,buff);
	if(flag == 1)
 		return 1;
	else 
		return 0; 
}


void passOne(char *inputFile){		// function performs pass one of the assembler
	char lineCpy[20];
	int idx = 0;
	FILE *input, *intermediate;
	input = fopen(inputFile, "r");
	intermediate = fopen("intermediate.txt", "w");
	
	printf("\n");
	printf("Address\tLabel\tOpcode\tOperand\n");
	printf("*******************************\n");
	
	fgets(line,20,input);

	while(line[0] == '.') 
		fgets(line,20,input);

	readLine();

	if(!strcmp(opcode,"START")) {
		strcat(operandHex,"0x");
		strcat(operandHex,operand); 
        	startAddr = strtol(operandHex,NULL,16);
        	LOCCTR = startAddr;
		address[idx++] = LOCCTR;
        	strcpy(programName,label);
		while(strlen(programName)!=6)
			  strcat(programName," ");	 	
        	fprintf(intermediate,"%s",line);
        	fgets(line,20,input);
		while(line[0] == '.') 
			fgets(line,20,input);
        }	
	else {
		programName[0]='\0';
           	startAddr=0x00;
           	LOCCTR=0x00;
		address[idx++] = LOCCTR;
        }
        printf("\n XXXX\t %s\t%s\t %s",label,opcode,operand);
 
        while(strcmp(lineCpy,"END")) {
        	readLine();
             	printf("\n %04X\t %s \t%s\t %s",LOCCTR,label,opcode,operand);
             	if(label[0]!='\0') 
			checkLabel();
             	checkOpcode();
		address[idx++] = LOCCTR;
		if(label[0]!='\0')
             		fprintf(intermediate,"%s %s %s\n",label,opcode,operand);
		else
			fprintf(intermediate,"%s %s\n",opcode,operand);
             	fgets(line,20,input);
		while(line[0] == '.') 
			fgets(line,20,input);
		strcpy(lineCpy, line);
		lineCpy[3] = '\0';
        }
        printf("\n XXXX\t\t%s\n",line);
        fprintf(intermediate,"%s",line);
 
 	fclose(intermediate);		
 	fclose(input);
}

void passTwo(char *fileName) {		// function performs pass two of the assembler
	FILE *intermediate, *output;
	char record[10000], part[20], value[6], lineCpy[20], operandNew[10], recordNew[10000], tempStr[10000], charStr[10], outputFile[20];
	int curTxtLen = 0, opcodeFound, operandFound, check, operandAddr, recordAddr, code, error = 0, partLen, addrCtr = 0, countr = 0, i = 0, j = 0, k = 0, l = 0, m, param = 0, tempAddr; 
	float testParam;
	
	fileName[strlen(fileName) - 3] = '\0';
	strcat(fileName, "obj");	
	strcpy(outputFile, fileName);
	intermediate = fopen("intermediate.txt", "r");
	output = fopen(outputFile, "w");
	fgets(line,20,intermediate);
	
	readLine();
	
	if(!strcmp(opcode,"START")) 
		fgets(line,20,intermediate);
	
	printf("\n\nObject code for the above SIC program :\n");
	printf("\nH^%s^%06X^%06X",programName,startAddr,length);
	fprintf(output,"H^%s^%06X^%06X",programName,startAddr,length);
    	recordAddr = startAddr; 
	record[0] = '\0';

	while(strcmp(lineCpy,"END")) {
		operandAddr = operandFound = opcodeFound = m = l = 0;
       		value[0] = part[0] = charStr[0] = '\0';
       		readLine();
		strcpy(lineCpy, line);
		lineCpy[3] = '\0';
		
		code = getHexCode(opcode);
		
		if(code != -1) {
			opcodeFound = 1;
			sprintf(part, "%02X", code);
			
			if(operand[0]!='\0') {  
				strcpy(operandNew,operand);
				operandNew[strlen(operand)-1] = '\0'; 
				if(isIndexed(operandNew)) { 
					for(check = 0; check < symbolCount; check++) { 
						if(!strcmp(symtab[check].symbol, operandIndex)) { 
							tempAddr = symtab[check].addr;
							tempAddr += 0x8000;
							sprintf(value, "%04X", tempAddr);
							strcat(part, value);
             						operandFound = 1;
						}
					}
				}
				else {
					for(check = 0; check < symbolCount; check++) { 
						if(!strcmp(symtab[check].symbol, operandNew)) {
							sprintf(value, "%04X", symtab[check].addr); 
             						strcat(part, value);
             						operandFound = 1;
						}
					}
				}
				if(!operandFound)
					strcat(part,"ERROR");
			}
		}
	
		if(!opcodeFound) { 
			if(!strcmp(opcode,"WORD")) {
				strcpy(operandNew,operand);
				operandNew[strlen(operand)-1] = '\0';
				partLen = strlen(operandNew);
				while(partLen != 6) {
					strcat(part, "0");
					partLen++;
				}
            			strcat(part,operandNew); 
            		}
			if(!strcmp(opcode,"BYTE")) {
				strcpy(operandNew,operand);
				operandNew[strlen(operand)-1] = '\0'; 
					for(l=0;operandNew[l]!='\0';l++) {
						if(operandNew[l] == '\'') {
							l++; 
							while(operandNew[l] != '\'') 
								charStr[m++] = operandNew[l++]; 
						}
					} 
				charStr[m] = '\0'; 
					if(operandNew[0] == 'C') {
						if(strlen(charStr) == 1) 
							strcat(part,"0000");
						if(strlen(charStr) == 2)
							strcat(part,"00");
						for(m=0;charStr[m]!='\0';m++) {
							sprintf(value,"%X",charStr[m]);
							strcat(part,value);
						}
					}
					if(operandNew[0] == 'X') {
						strcat(value,charStr);
						strcat(part,value);
					}
			}
        	}

		if(part[0] != '\0') {			
			strcat(record, "^"); 
         		strcat(record, part); 
         		curTxtLen += strlen(part); 
		}	
		fgets(line, 20, intermediate);
	}
	

	while(j < strlen(record)) {
		if((j!=0) && record[j] == '^') 
			addrCtr++;	
		if((j % 70 == 0) && (j != 0)) {
			recordNew[i++] = '\n';
			recordNew[i++] = 'T';
			recordNew[i++] = '^';
			sprintf(tempStr, "%06X", address[addrCtr]);
			for(k=0; k<strlen(tempStr); k++)
				recordNew[i++] = tempStr[k];
			recordNew[i++] = '^'; 
			testParam = (float) (strlen(record) - j)/70;
			if(testParam > 1) {
				tempStr[0] = '1';
				tempStr[1] = 'E';
			}
			else {
				param = strlen(record) % 70;
				param = (param-(param/7))/2;
				sprintf(tempStr, "%02X", param);
			}
			for(k=0; k<2; k++)
				recordNew[i++] = tempStr[k];	
		}
		recordNew[i++] = record[j++];
		countr++;
	}

	recordNew[i] = '\0';

	if(strlen(record) > 70) 
		curTxtLen = 30;
	else
		curTxtLen = curTxtLen/2;

	printf("\nT^%06X^%02X%s",recordAddr, curTxtLen, recordNew); 
 	fprintf(output,"\nT^%06X^%02X%s",recordAddr, curTxtLen, recordNew);
    	printf("\nE^%06X\n", startAddr);
    	fprintf(output,"\nE^%06X\n", startAddr);
    	remove("intermediate.txt");
    	fclose(output);
	
}    

void checkError(char *inputFile) {		// function checks for errors in the source code;
						// if errors are found then assembler informs the user about the errors and terminates 							// operation
	FILE *input;
	char lineCpy[20]={'\0'}, operandNew[20];
	int code, error=0, i, found, lineCtr = 0;
	
	input = fopen(inputFile, "r");
	fgets(line,20,input);
	readLine();
	lineCtr++;
	while(line[0] == '.') {
		fgets(line,20,input);
		lineCtr++;
	}

	if(!strcmp(opcode,"START")) { 
		if(strlen(programName) > 6) { 
				printf("\nERROR: Max Length of Pgm Name is 6 characters\n");
				flag=1;
		}
		fgets(line,20,input); 
		while(line[0] == '.') {
			fgets(line,20,input);
			lineCtr++;
		}
	}

	strcpy(lineCpy, line);

	while(strcmp(lineCpy,"END")) { 
		found=0;
		readLine();
		lineCtr++;	
		strcpy(lineCpy, line);
		lineCpy[3] = '\0';

		code = getHexCode(opcode);
		
		if(code == -1) {
			error = isAssemblerDirective(opcode);
			if(error == -1) {
				printf("\nERROR: %s in line %d\n", opcode, lineCtr);
				flag=1;
			}
			else break;
		}
 
		strcpy(operandNew,operand);
		operandNew[strlen(operand)-1] = '\0'; 

		if(isIndexed(operandNew)) {
			for(i=0;i<symbolCount;i++) {
				if(!strcmp(operandIndex,symtab[i].symbol)) 
					found=1;
			}
			if(!found) {
				printf("\nERROR: %s in line %d is undefined\n",operandIndex,lineCtr);				
				flag=1;
			}
		}

		else {
			for(i=0;i<symbolCount;i++) {
				if(!strcmp(operandNew,symtab[i].symbol)) 
					found=1;
			}
			if(!found) {
				printf("\nERROR: %s in line %d is undefined\n",operandNew,lineCtr);				
				flag=1;
			}
		}
 
		fgets(line,20,input);
		while(line[0] == '.') {
			fgets(line,20,input);
			lineCtr++;
		}
	}

	fclose(input);
}

int main (int argc, char *argv[]) {
	if((argc > 2) || (argc <= 1)) {
		printf("Syntax: ssasm <inputFileName>\n");
		return 0;
	}
	writeOpcodeSheet();
	printf("\n**********************************************************************************\n"); 
	printf("\t\tSIC machine assembler by Suhas H and Sumukha TV\n\n");
	passOne(argv[1]);
	checkError(argv[1]);		// check if there are any errors in the source code
	length = LOCCTR - startAddr;
	if(flag == 0)			// perform pass two only if no errors are found
   		passTwo(argv[1]); 
	else
		printf("\nAssembler Terminated!\n"); 
	printf("\n**********************************************************************************\n\n");        
	return 0;
}

