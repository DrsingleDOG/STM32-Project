<p>STM32 LIBERARY V3.50  UPDATE<br>This is about crotex-m3 Systick<br>Because Systick belongs to kernel .It’s controled by systemclock.So there is no liberary for systick in V3.5.<br>When we set up Systick;<br>We can do:<br>‘’’/<strong><strong><strong><strong><strong><strong><strong><strong><strong><strong><strong><strong>**</strong></strong></strong></strong></strong></strong></strong></strong></strong></strong></strong></strong>/</p>
<p>//SysTick interrupt servicing<br>void SysTick_Handler()<br>{<br>    //what you want to do<br>}</p>
<p>void main()<br>{<br>    ….<br>    SysTick_Config(value);//time  =  ( (Value(load) - 0 )  + 1 ) / f  “f:0 AHB/8  1 AHB”<br>    ….<br>}</p>
<p>/<strong>**</strong>in V3.5 we must use SysTick_Handler() function to handle Systick<strong><strong><em>**</em></strong></strong>/</p>
<p>otherwise void SysTick_CLKSourceConfig(u32 SysTick_CLKSource) is not a useful function.<br>‘’’</p>
