#include"stm32f10x.h"
#include"stdio.h"



void RCC_Configuration(void);	//ʱ��RCC����
void GPIO_Configuration(void);  //GPIO�ڵ�����
void USART_Configuration(void); //����ͨ��USART����
void NVIC_Configuration(void);  //Ƕ���ж�����NVIC����
void EXTI_Configuration(void);  //�ⲿ�ж�EXTI����
void Systick_Configuration(void);
u16 sec=30,min=0;
int main(void)
{
	u8 sec,min;
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();
	//NVIC_Configuration();
	//EXTI_Configuration();
	Systick_Configuration();
	SysTick_Config(13000000);
	
	while(1);

}

void delay_ms(u16 time) 
{         
	u16 i=0;      
	while(time--)   
  	{       
  		 i=12000;     
			while(i--);        
  	} 
}

void SysTick_Handler()
{
			
	
	if(sec == 60)
	{
		sec = 0;
		min++;		
	}
	else
	{
		sec++;	
		printf("The time is : %d:%d\t",min,sec);
	}
	

}

/****************************************************************************
name:RCC_Configuration                       Ouput:None													   	
discribe:Set system each secion clock		 return:None
input:None
****************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;   //����ö���ͱ���
	RCC_DeInit();					//��λϵͳʱ������
	RCC_HSEConfig(RCC_HSE_ON);		//��HSE
	HSEStartUpStatus=RCC_WaitForHSEStartUp();//�ȴ�HSE����
	/*�ж�HSE�����Ƿ�ɹ����������if()*/
	if(HSEStartUpStatus==SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);	//ѡ��HCLK(AHB�����豸ʱ��)ʱ��ԴΪSYSCLK 1��Ƶ
		RCC_PCLK2Config(RCC_HCLK_Div1);		//ѡ��PCLK2ʱ��ԴΪHCLK(AHB)1��Ƶ
		RCC_PCLK1Config(RCC_HCLK_Div2);		//ѡ��PCLK1ʱ��ԴΪHCLK(AHB)2��Ƶ
		FLASH_SetLatency(FLASH_Latency_2);	//����FLASH��ʱ������2
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//ʹ��FLASHԤȡ����
		/*ѡ��PLLʱ��ԴΪHSE 1��Ƶ����ƵΪ9 ����PLL=8*9=72MHz*/
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);					//ʹ��PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//�ȴ�����ȶ�
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);		//ѡ��SYSCLKʱ��ԴΪPLL
		while(RCC_GetSYSCLKSource()!=0x08);				//�ȴ�PLL��ΪSYSCLKʱ��Դ
	}
	/*����USART1��GPIOAʱ��*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
}

/*******************************************************************************
name		:GPIO_Configuration			output		:none
discribe	:Set GPIO founction			return		:none
input		:none
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����GPIOA.2 ��GPIOA.3 Ϊ����������ת��Ϊ50MHz*/
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;			 //����LED��� D2
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOG, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			 //����LED��� D5
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			 
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			 
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			 
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);  //EXIT 0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);  //EXIT 1
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);  //EXIT 2

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOA,ENABLE);

//	GPIO_Cmd(GPIOD|GPIOG,ENABLE); 
}

/*******************************************************************************
name		:USART_Configuration			output		:none
discribe	:Set USART founction			return		:none
input		:none
*******************************************************************************/
/*
USART1 �������ţ�
PA8/USART1-CK
PA9/USART1-TX
PA10/USART1-RX
PA11/USART1-CTS
PA12/USART1-RTS
*/
void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;	
	USART_ClockInitTypeDef USART_ClockInitStructure;
	/*������ 9600  8λ���ݳ���  1��ֹͣλ ��У��λ
	  ����Ӳ��������  ��ֹUSARTʱ�� ʱ�Ӽ��Ե�  �ڵڶ������ز�������
	  ���һλ��ʱ�����ݵ�ʱ�����岻��SCLK���*/
	USART_InitStructure.USART_BaudRate =9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1 , &USART_ClockInitStructure);
	USART_Cmd(USART1, ENABLE);
}
/*******************************************************************************
name		:NVIC_Configuration			output		:none
discribe	:Set NVIC founction			return		:none
input		:none
*******************************************************************************/
//void NVIC_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	#ifdef VECT_TAB_FLASH
//		NVIC_SetVectorTable(NVIC_VecTab_RAM,0x0);
//	#else
//		NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x0);
//	#endif
//	/* Configure the Priority Grouping with 1 bit */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	/* Enable EXIT 0 interrupt with Preemption Priority 2 and Sub
//   Priority as 0 */
//	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
//	NVIC_Init(&NVIC_InitStructure);
//	/* Enable EXIT 1 interrupt with Preemption Priority 1 and Sub
//   Priority as 0 */ 
//	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
//	NVIC_Init(&NVIC_InitStructure);
//	/* Enable EXIT 1 interrupt with Preemption Priority 0 and Sub
//   Priority as 0 */ 
//	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
//	NVIC_Init(&NVIC_InitStructure);	
//}
/****************************************************************************
name:Systick_Configuration                       Ouput:None
discribe:Set Systick clock		 				 return:None
input:None
****************************************************************************/
void Systick_Configuration(void)
{
	 SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/*******************************************************************************
name		:EXTI_Configuration			output		:none
discribe	:Set EXTI founction			return		:none
input		:none
*******************************************************************************/
//void EXTI_Configuration(void)
//{
//	/* Enables external lines 12 and 14 interrupt generation on falling
//edge */
//	EXTI_InitTypeDef EXTI_InitStructure;
//	EXTI_InitStructure.EXTI_Line = EXTI_Line0| EXTI_Line1| EXTI_Line2;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);	
//}
int fputc(int ch,FILE *f)
{
	USART_SendData(USART1,(u8) ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	return ch;
}