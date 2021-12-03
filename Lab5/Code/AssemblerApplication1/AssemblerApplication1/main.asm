
.nolist
.include "m2560def.inc"
.list
.def _logic  = r0;  
.def _temp1 = r16
.def _temp2 = r17
.def _temp3_left = r18
.def _algo1_register = r20 
.def _temp1_left = r27
.def _temp2_right = r28
.def _algo3_register = r21
.def _algo1_counter = r22
.def _algo3_counter = r23
.def _temp4_for_delay = r24
.def _temp5_for_delay = r25
.def _temp6_for_delay = r26



    .CSEG
    .org 0x00
  rjmp reset  
    .org OC4Aaddr
  rjmp TIMER4_COMPA

TIMER4_COMPA:
  in _temp1, SREG
  push _temp1
  sbrs _logic, 0
  rjmp algorithm_2
  cpi _algo1_counter, 4
  brlo continue 
  clr _algo1_register
  out PORTC, _algo1_register
   
  clt
  clr _algo1_register 
  bld _logic, 0
  rjmp algorithm_2
  
  continue:
  
    out PORTC, _algo1_register 
    lsl _temp1_left
  lsr _temp2_right
    mov _algo1_register, _temp1_left
    or  _algo1_register, _temp2_right
    inc _algo1_counter

algorithm_2:
  sbrs _logic, 1
  rjmp return
  

  cpi _algo3_counter, 8
  brlo continue_3
  
  clr _algo3_register
  sts PORTK, _algo3_register
  clt
  bld _logic, 1
  rjmp return
  continue_3:
    sts PORTK, _algo3_register
 
  lsl _temp3_left
    mov _algo3_register, _temp3_left
    
    inc _algo3_counter
return:
  pop _temp1
  out SREG, _temp1
  reti

reset:
  ldi  _temp1, low(RAMEND)
  out SPL, _temp1
  ldi _temp1, high(RAMEND)
  out SPH, _temp1
  ldi _temp1, 0xFF
  ldi _temp2, 0x00
  out DDRC, _temp1
  sts DDRK, _temp1
  out PORTC, _temp2
  sts PORTK, _temp2
  ldi _temp1, (1<<DDB4) | (1<<DDB6)
  out PORTA, _temp1
  
 

  sbi DDRA, 0
  cbi PORTA, 0

  ldi _temp1, 0x0C
  ldi _temp2, 0x34
  sts  OCR4AH, _temp1
  sts OCR4AL, _temp2
  ldi _temp1, 0x00
  sts TCCR4A, _temp1
  ldi _temp1, (1 << WGM42) | (1 << CS42) | (1 << CS40)
  sts TCCR4B, _temp1
  ldi _temp1, (1 << OCIE4A)
  sts TIMSK4, _temp1


  clr _logic
  clr _temp1
  clr _temp2
  clr _temp3_left

  clr _temp2_right
  clr _algo1_register
  clr _temp1_left
  clr _algo1_counter
  clr _algo3_register
  clr _algo3_counter
  clr _temp4_for_delay      
  clr _temp5_for_delay         
  clr _temp6_for_delay
  sei 

main:  
    clt
    sbis PINA, 4
    rjmp next_button
    rcall delay
 
    sbis PINA, 4
    rcall button_1_is_pressed
  next_button:
     sbis PINA, 6
    rjmp main
    rcall delay
     sbis PINA, 6
    rcall button_2_is_pressed
    rjmp main

button_1_is_pressed:
    clr _algo1_counter
     ldi _temp1_left,  1
    ldi _temp2_right, 1<<7
   mov _algo1_register, _temp1_left
     or _algo1_register, _temp2_right
    set
    bld _logic, 0
    rcall buzzer
    ret

button_2_is_pressed:
    clr _algo3_counter
    ldi _temp3_left,  1
  
   mov _algo3_register,_temp3_left
    
  
    set
    bld _logic, 1
    rcall buzzer
    ret
  
buzzer:
  sbi  PORTA, 0
  rcall delay
  cbi  PORTA, 0

  ret  
       
delay:       
  ldi _temp4_for_delay, 0xFF      
  ldi _temp5_for_delay, 0xFF
  ldi _temp6_for_delay, 1 
  del:                
    subi _temp4_for_delay, 1       
    sbci _temp5_for_delay, 0          
    sbci _temp6_for_delay, 0  
  brcc del     
ret               


  .ESEG