----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    22:21:50 03/03/2015 
-- Design Name: 
-- Module Name:    test_env - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity test_env is
    Port ( clk : in  STD_LOGIC;
           btn : in  STD_LOGIC_VECTOR (3 downto 0);
           sw : in  STD_LOGIC_VECTOR (7 downto 0);
           led : out  STD_LOGIC_VECTOR (7 downto 0);
           an : out  STD_LOGIC_VECTOR (3 downto 0);
           cat : out  STD_LOGIC_VECTOR (6 downto 0);
           dp : out  STD_LOGIC);
end test_env;

architecture Behavioral of test_env is





------------Componenta MPG-------------
component MPG is
	port ( btn: in std_logic;
		clock: in std_logic;
		enable: out std_logic);
end component;
---------------------------------------

------------Componenta SSD-------------
component SSD is
port( clk: in STD_LOGIC;
		digits: in STD_LOGIC_VECTOR(15 DOWNTO 0);
		an: out STD_LOGIC_VECTOR(3 DOWNTO 0);
		cat: out STD_LOGIC_VECTOR(6 DOWNTO 0));
end component;
---------------------------------------

-------------Componenta IFetch---------
component IFetch is
	Port (WE : in std_logic;
			reset : in std_logic;
			clk: in std_logic;
			BranchAddress : in std_logic_vector(15 downto 0);
			JumpAddress : in std_logic_vector(15 downto 0);
			JCS : in std_logic;
			PCSrc : in std_logic;
			Instruction : out std_logic_vector(15 downto 0);
			PC : out std_logic_vector(15 downto 0));
end component;
---------------------------------------

----------CU Signals---------
signal RegDst: std_logic;
signal ExtOp: std_logic;
signal ALUSrc: std_logic;
signal Branch: std_logic;
signal Jump: std_logic;
signal ALUOp: std_logic_vector(2 downto 0);
signal MemWrite: std_logic;
signal MemtoReg: std_logic;
signal RegWrite: std_logic;
-----------------------------

-------------Componenta IDecode--------
component IDecode is
	Port ( clk: in std_logic;
			Instruction: in std_logic_vector(15 downto 0);
			WriteData: in std_logic_vector(15 downto 0);
			RegWrite: in std_logic;
			RegWrite2: in std_logic;
			RegDst: in std_logic;
			ExtOp: in std_logic;
			ReadData1: out std_logic_vector(15 downto 0);
			ReadData2: out std_logic_vector(15 downto 0);
			Ext_Imm : out std_logic_vector(15 downto 0);
			Func : out std_logic_vector(2 downto 0);
			SA : out std_logic);		
end component;
---------------------------------------

-------------Componenta ControlUnit----
component ControlUnit is
Port	( Instr:in std_logic_vector(2 downto 0);
			 RegDst: out std_logic;
			 ExtOp: out std_logic;
			 ALUSrc: out std_logic;
			 Branch: out std_logic;
			 Jump: out std_logic;
			 ALUOp: out std_logic_vector(2 downto 0);
			 MemWrite: out std_logic;
			 MemtoReg: out std_logic;
			 RegWrite: out std_logic);
end component;
---------------------------------------

-------------Componenta Memory---------
component MEM is
	port(
			clk: in std_logic;--
			ALURes : in std_logic_vector(15 downto 0);
			WriteData: in std_logic_vector(15 downto 0);
			MemWrite: in std_logic;		
			MemWriteCtrl: in std_logic;				
			MemData:out std_logic_vector(15 downto 0);--
			ALURes2 :out std_logic_vector(15 downto 0)--
	);
end component;
---------------------------------------

-------------Componenta ExUnit---------
component ExecutionUnit is
Port(
	PCOut:in std_logic_vector(15 downto 0);
	RD1: in std_logic_vector(15 downto 0);
	RD2: in std_logic_vector(15 downto 0);
	Ext_Imm: in std_logic_vector(15 downto 0);
	Func: in std_logic_vector(2 downto 0);
	SA: in std_logic;
	ALUSrc: in std_logic;
	ALUOp: in std_logic_vector(2 downto 0);
	BranchAddress: out std_logic_vector(15 downto 0);
	ALURes: out std_logic_vector(15 downto 0);
	ZeroSignal: out std_logic);
end component;
---------------------------------------


signal enable: STD_LOGIC;    --Instruction Fetch - enable
signal enable2: STD_LOGIC;	  --Instruction Fetch - reset
signal BranchAddress:std_logic_vector(15 downto 0);  	   --branch address used for IF
signal JumpAddress:std_logic_vector(15 downto 0); 		   --jump address used for IF
signal SSDOUT : std_logic_vector(15 downto 0):=X"0000";  --afisare SSD
signal InstrOut: std_logic_vector(15 downto 0);			   --next instruction  
signal PCout: std_logic_vector(15 downto 0);				   --program counter	 
signal ALURes: std_logic_vector(15 downto 0);			   --ALU result
signal ZeroSignal: std_logic;										--Zero Signal used for Branch
signal RD1: std_logic_vector(15 downto 0);					--Read Data 1 
signal RD2: std_logic_vector(15 downto 0);					--Read Data 2
signal Ext_Imm : std_logic_vector(15 downto 0);				--Ext_Imm
signal Func :std_logic_vector(2 downto 0);					--Func - Instruction(2 downto 0)
signal SA : std_logic;												--Shift Amount
signal MemData: std_logic_vector(15 downto 0);				--Mem Data = Read Data --Memory -- OUT
signal ALUResFinal: std_logic_vector(15 downto 0);			--ALU Result - OUT from Memory
signal WriteDataReg: std_logic_vector(15 downto 0);		--WriteData for RegFile
signal PCSrc:std_logic;												--PCSrc signal = BranchAddress and ZeroSignal

begin

dp <= '0';


------Instantiere componenta IFetch--------------
IFetch1: IFetch port map(enable,enable2,clk,BranchAddress,JumpAddress,Jump,PCSrc,InstrOut,PCout);
-------------------------------------------------

------Instantiere componenta IDecode-------------
IDecode1 : IDecode port map (clk,InstrOut,WriteDataReg,RegWrite,enable,RegDst,ExtOp,RD1,RD2,Ext_Imm,Func,SA);
-------------------------------------------------

------Instantiere componenta CtrlUnit------------
CUnit1 : ControlUnit port map (InstrOut(15 downto 13),RegDst,ExtOp,ALUSrc,Branch,Jump,ALUOp,MemWrite,MemtoReg,RegWrite);
-------------------------------------------------

------Instantiere componenta ExUnit--------------
ExUnit1 : ExecutionUnit port map(PCOut,RD1,RD2,Ext_Imm,Func,SA,ALUSrc,ALUOp,BranchAddress,ALURes,ZeroSignal);
-------------------------------------------------

------Instantiere componenta Memory--------------
Memory1 : MEM port map(clk,ALURes,RD2,MemWrite,enable,MemData,ALUResFinal);
-------------------------------------------------


------Instantiere componenta SSD, s1-------------
s1 :SSD port map(clk,SSDOUT,an,cat);
-------------------------------------------------


------Instantiere componenta MPG, c1-------------
c1 :MPG port map(btn(0),clk,enable);
c2 :MPG port map(btn(1),clk,enable2);
-------------------------------------------------

------------MUX MEM_ALU -> WriteRegister---------
process(MemtoReg,ALUResFinal,MemData)
begin
	case (MemtoReg) is
		when '1' => WriteDataReg<=MemData;
		when '0' => WriteDataReg<=ALUResFinal;
		when others => WriteDataReg<=WriteDataReg;
	end case;
end process;	
-------------------------------------------------

-------------------AND Zero+Branch---------------
PCSrc<=ZeroSignal and Branch;
-------------------------------------------------

-----------------JumpAddress---------------------
JumpAddress<=PCOut(15 downto 14) & InstrOut(13 downto 0);
-------------------------------------------------

---------MUX pentru afisare----------------------
process(InstrOut,PCout,RD1,RD2,Ext_Imm,ALURes,MemData,WriteDataReg,sw)
begin
	case(sw(7 downto 5)) is
		when "000"=>
				SSDOut<=InstrOut;			-----AFISARE INSTROUT-----
		when "001"=>
				SSDOut<=PCout;				-----AFISARE PCOUT-----
		when "010"=>
				SSDOut<=RD1;				-----AFISARE ReadData1-----
		when "011"=>
				SSDOut<=RD2;				-----AFISARE ReadData2-----
		when "100"=>
				SSDOut<=Ext_Imm;			-----AFISARE EXT_IMM-----
		when "101" =>
				SSDOut<=ALURes;			-----AFISARE ALUres-----		
		when "110"=>
				SSDOut<=MemData;			-----AFISARE MemData-----
		when "111"=>
				SSDOut<=WriteDataReg;	-----AFISARE WriteData - RegisterFile-----
		when others=>
				SSDOut<=X"AAAA";
	end case;
end process;
-------------------------------------------------	

---------MUX pentru afisarea pe leduri a semnalelor de control------------
process(RegDst,ExtOp,ALUSrc,Branch,Jump,MemWrite,MemtoReg,RegWrite,sw,ALUOp)
begin
	if sw(0)='0' then		
		led(7)<=RegDst;
		led(6)<=ExtOp;
		led(5)<=ALUSrc;
		led(4)<=Branch;
		led(3)<=Jump;
		led(2)<=MemWrite;
		led(1)<=MemtoReg;
		led(0)<=RegWrite;
		
	else
		led(2 downto 0)<=ALUOp(2 downto 0);
		led(7 downto 3)<="00000";
	end if;
end process;	
---------------------------------------------------------------------------

end Behavioral;

