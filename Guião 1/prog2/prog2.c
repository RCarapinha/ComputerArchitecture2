int main(void) 
{ 
  char c; 
  while (1) 
  { 
     while ((c = inkey()) == 0); 
     if (c == '\n') 
      break; 
     printStr("Key pressed\n"); 
  } 
  return 0; 
} 
