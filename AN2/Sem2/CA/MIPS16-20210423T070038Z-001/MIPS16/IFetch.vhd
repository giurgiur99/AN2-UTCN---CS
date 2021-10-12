----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:24:48 03/26/2015 
-- Design Name: 
-- Module Name:    IF - Behavioral 
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

entity IFetch is
	Port (WE : in std_logic;
			reset : in std_logic;
			clk: in std_logic;
			BranchAddress : in std_logic_vector(15 downto 0);
			JumpAddress : in std_logic_vector(15 downto 0);
			JCS : in std_logic;
			PCSrc : in std_logic;
			Instruction : out std_logic_vector(15 downto 0);
			PC : out std_logic_vector(15 downto 0):=X"0000");
end IFetch;

architecture Behavioral of IFetch is

--------------Memorie ROM--------------
type rom_type is array(0 to 255) of std_logic_vector(15 downto 0);
signal ROM: rom_type := (



-------------PROGRAM DE TEST-------------
--Acest program testeaza toate instructiunile implementate,
--folosind scrierea si citirea din memorie pentru verificare
--si, de asemenea, instructiunile de salt beq si jump
--		B"000_001_000_010_0_000",   --X"0420"  	--add
--		B"000_011_010_010_0_001",   --X"0d21"		--sub
--		B"000_010_000_010_1_010",   --X"082A"		--sll
--		B"000_010_000_010_1_011",   --X"082b"		--srl
--		B"000_011_010_100_0_100",   --X"0d44"		--and
--		B"000_101_100_100_0_101",   --X"1645"		--or
--		B"000_100_100_100_0_110",   --X"1246"		--xor
--		B"000_010_011_100_0_111",   --X"09C7"		--slt
--		B"001_000_100_0000100",   --X"2204"			--addi
--		B"010_001_101_0000000",   --X"4680"			--lw
--		B"011_100_101_0000000",   --X"7280"			--sw
--		B"100_001_001_0000001",   --X"8481"			--beq
--		B"101_100_101_0000100",   --X"b284"			--andi
--		B"110_101_110_0000011",   --X"d703"			--ori
--		B"111_0000000000011",   --X"E003"			--j
-----------------------------------------		
		
		

--------------FIBONACCI------------------		
--Acest program calculeaza sirului lui Fibonacci
--incarcand initial 0 si 1 in 2 registri.
--Se efectueaza scrierea in memorie la 2 adrese diferite
--si apoi citirea de la aceleasi adrese pentru a verifica 
--corectitudinea.

--Calculul elementelor din sir se face intr-o bucla, folosind
--instructiunea jump

		B"001_000_001_0000000",  --X"2080"	--addi $1,$0,0
		B"001_000_010_0000001",	 --X"2101"	--addi $2,$0,1	
		B"001_000_011_0000000",	 --X"2180"	--addi $3,$0,0	
		B"001_000_100_0000001",	 --X"2201"	--addi $4,$0,1
		B"011_011_001_0000000", --X"6C80"   --sw $1,0($3)
		B"011_100_010_0000000", --X"7100"   --sw $2,0($4)
		B"010_011_001_0000000", --X"4C80"   --lw $1,0($3)
		B"010_100_010_0000000", --X"5100"   --lw $2,0($4)
		B"000_001_010_101_0_000", --X"0550" --add $5,$1,$2
		B"000_000_010_001_0_000", --X"0110" --add $1,$0,$2
		B"000_000_101_010_0_000", --X"02A0" --add $2,$0,$5
		B"111_0000000001000", --X"E008"     --j 8
-----------------------------------------
			others => X"0000");
---------------------------------------


signal PCounter, PCAux, NextAdr, AuxSgn: std_logic_vector(15 downto 0) :=X"0000";

begin


----------MUX_JA_AuxSgn_Jump-----------
process(JCS,AuxSgn,JumpAddress)
begin
	case(JCS) is
		when '0' => NextAdr <= AuxSgn;
		when '1' => NextAdr <= JumpAddress;
		when others => NextAdr <= X"0000";
	end case;
end process;	
---------------------------------------

-----------MUX_BA_PCAux_PCSrc----------
process(PCSrc,PCAux,BranchAddress)
begin
	case (PCSrc) is 
		when '0' => AuxSgn <= PCAux;
		when '1' => AuxSgn<=BranchAddress;
		when others => AuxSgn<=X"0000";
	end case;
end process;	
---------------------------------------

-----------Program Counter-------------
process(clk,reset)
begin
	if Reset='1' then
		PCounter<=X"0000";
	else if rising_edge(clk) and WE='1' then
		PCounter<=NextAdr;
		end if;
		end if;
end process;
---------------------------------------

-----------Instruction OUT-------------
Instruction<=ROM(conv_integer(PCounter(7 downto 0)));
---------------------------------------

---------------PC+1--------------------
PCAux<=PCounter + '1';
---------------------------------------

-------------PC_OUT(PC+1)--------------
PC <= PCAux;
---------------------------------------

end Behavioral;

