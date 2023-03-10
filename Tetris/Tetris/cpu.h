void cpu_freq(void){
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;
	MDR_RST_CLK -> UART_CLOCK |= (1<< RST_CLK_UART_CLOCK_UART2_CLK_EN_Pos);	
	MDR_RST_CLK -> HS_CONTROL = (0x0 << RST_CLK_HS_CONTROL_HSE_BYP_Pos) | (0x1 << RST_CLK_HS_CONTROL_HSE_ON_Pos);
	
	while ( (MDR_RST_CLK -> CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY) != RST_CLK_CLOCK_STATUS_HSE_RDY );
	
	MDR_RST_CLK -> CPU_CLOCK = (0x2 << RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos);
	MDR_RST_CLK -> PLL_CONTROL = (0x9 << RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos) | (0x1 << RST_CLK_PLL_CONTROL_PLL_CPU_ON_Pos);
	MDR_RST_CLK -> PLL_CONTROL |= (RST_CLK_PLL_CONTROL_PLL_CPU_PLD);
	MDR_RST_CLK -> PLL_CONTROL &= ~(RST_CLK_PLL_CONTROL_PLL_CPU_PLD);
	while ( (MDR_RST_CLK -> CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY) != RST_CLK_CLOCK_STATUS_PLL_CPU_RDY );
	
	MDR_RST_CLK -> CPU_CLOCK |= (0x1 << RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos) | (0x1 << RST_CLK_CPU_CLOCK_HCLK_SEL_Pos);
}