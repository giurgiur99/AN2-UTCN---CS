----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:13:29 03/05/2015 
-- Design Name: 
-- Module Name:    SSD - Behavioral 
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

entity SSD is
port( clk: in STD_LOGIC;
		digits: in STD_LOGIC_VECTOR(15 DOWNTO 0);
		an: out STD_LOGIC_VECTOR(3 DOWNTO 0);
		cat: out STD_LOGIC_VECTOR(6 DOWNTO 0));
end SSD;

architecture Behavioral of SSD is

signal countSSD: STD_LOGIC_VECTOR(15 DOWNTO 0);
signal mux_out:STD_LOGIC_VECTOR(3 DOWNTO 0);

begin

process(clk)
begin
	if rising_edge(clk) then
		countSSD<=countSSD+1;
		end if;
end process;



process(countSSD(15 downto 0),digits)
begin
	case (countSSD(15 downto 14)) is
		when "00" => mux_out <= digits(3 downto 0); 
						an<="1110";
		when "01" => mux_out <= digits(7 downto 4); 
						an<="1101";
		when "10" => mux_out <= digits(11 downto 8); 
						an<="1011";
		when "11" => mux_out <= digits(15 downto 12); 
						an<="0111";
		when others => mux_out<="0000";
					an <="1111";
	end case;
end process;




--HEX-to-seven-segment decoder
--   HEX:   in    STD_LOGIC_VECTOR (3 downto 0);
--   LED:   out   STD_LOGIC_VECTOR (6 downto 0);
-- 
-- segment encoinputg
--      0
--     ---  
--  5 |   | 1
--     ---   <- 6
--  4 |   | 2
--     ---
--      3
   
	
	
	
    with mux_out Select
   cat<= "1111001" when "0001",   --1
         "0100100" when "0010",   --2
         "0110000" when "0011",   --3
         "0011001" when "0100",   --4
         "0010010" when "0101",   --5
         "0000010" when "0110",   --6
         "1111000" when "0111",   --7
         "0000000" when "1000",   --8
         "0010000" when "1001",   --9
         "0001000" when "1010",   --A
         "0000011" when "1011",   --b
         "1000110" when "1100",   --C
         "0100001" when "1101",   --d
         "0000110" when "1110",   --E
         "0001110" when "1111",   --F
         "1000000" when others;   --0
 
    
					









end Behavioral;

