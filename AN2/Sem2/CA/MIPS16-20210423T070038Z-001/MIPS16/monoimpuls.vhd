----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    23:08:24 03/03/2015 
-- Design Name: 
-- Module Name:    monoimpuls - Behavioral 
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

entity MPG is
	port ( btn: in std_logic;
		clock: in std_logic;
		enable: out std_logic);
end MPG;

architecture Behavioral of MPG is
signal count: std_logic_vector(15 downto 0):= x"0000";
signal enable_reg: std_logic;
signal reg1: std_logic;
signal reg2: std_logic;
signal reg3: std_logic;
begin

process(clock)
begin
	if rising_edge(clock) then
		count<=count+1;
	end if;
end process;

enable_reg <= '1' when count(15 downto 0)=x"FFFF" else '0';

process(clock)
begin
	if rising_edge(clock) and enable_reg='1' then
		reg1<=btn;
	end if;
end process;

process(clock)
begin
	if rising_edge(clock) then
		reg2<=reg1;
		reg3<=reg2;
	end if;
end process;

enable<= reg2 and not(reg3);

end Behavioral;

