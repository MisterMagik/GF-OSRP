-- phpMyAdmin SQL Dump
-- version 5.2.1deb1+deb12u1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Apr 07, 2026 at 07:49 PM
-- Wersja serwera: 10.11.14-MariaDB-0+deb12u2
-- Wersja PHP: 8.2.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `srv82617`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Accounts`
--

CREATE TABLE `Accounts` (
  `ID` int(3) NOT NULL,
  `Name` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Password` varchar(65) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Salt` varchar(17) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `IP` varchar(16) NOT NULL DEFAULT '127.0.0.1',
  `Recommender` varchar(25) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Date` varchar(64) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `LastDate` varchar(64) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '''Brak''',
  `AntiCrash` int(1) NOT NULL DEFAULT 0,
  `LastCrash` int(1) NOT NULL DEFAULT 0,
  `PP` int(9) NOT NULL DEFAULT 0,
  `PendingPP` int(9) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Accounts`
--

INSERT INTO `Accounts` (`ID`, `Name`, `Password`, `Salt`, `IP`, `Recommender`, `Date`, `LastDate`, `AntiCrash`, `LastCrash`, `PP`, `PendingPP`) VALUES
(14, 'steeZ', '4739BE9FC5F25A4EB212C87DB59DB7D2C635137BBC8425E064B172DF695BC227', '8>sM=hrqNrMs:Z5R', '127.0.0.1', 'Brak', '24/03/2026 21:14:11', '24/03/2026 21:14:11', 1, 1, 0, 0),
(15, 'MisterMagik', '1BF6BF511911B8D0CF5655EE3BE6E55A53D7BEC032BBB87FD00D537D27F3CD34', '/@i0XpN>RnmKbmMk', '83.10.217.96', 'Brak', '27/03/2026 16:47:51', '27/03/2026 16:47:51', 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Characters`
--

CREATE TABLE `Characters` (
  `ID` int(11) NOT NULL,
  `AID` int(11) DEFAULT NULL,
  `Name` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `Date` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '00/00/0000',
  `Level` int(3) NOT NULL DEFAULT 0,
  `AdminLevel` int(4) NOT NULL DEFAULT 0,
  `DonateRank` int(1) NOT NULL DEFAULT 0,
  `UpgradePoints` int(1) NOT NULL DEFAULT 0,
  `ConnectedTime` int(3) NOT NULL DEFAULT 0,
  `Registered` int(1) NOT NULL DEFAULT 0,
  `Sex` int(1) NOT NULL DEFAULT 0,
  `Age` int(2) NOT NULL DEFAULT 0,
  `Continent` int(1) NOT NULL DEFAULT 0,
  `Origin` int(1) NOT NULL DEFAULT 0,
  `CK` int(1) NOT NULL DEFAULT 0,
  `Muted` int(3) NOT NULL DEFAULT 0,
  `Respect` int(3) NOT NULL DEFAULT 0,
  `Money` int(9) NOT NULL DEFAULT 0,
  `Bank` int(9) NOT NULL DEFAULT 0,
  `Crimes` int(3) NOT NULL DEFAULT 0,
  `Kills` int(5) NOT NULL DEFAULT 0,
  `Deaths` int(5) NOT NULL DEFAULT 0,
  `Arrested` int(5) NOT NULL DEFAULT 0,
  `WantedDeaths` int(3) NOT NULL DEFAULT 0,
  `Phonebook` int(1) NOT NULL DEFAULT 0,
  `LottoNr` int(5) NOT NULL DEFAULT 0,
  `Fishes` int(9) NOT NULL DEFAULT 0,
  `BiggestFish` int(3) NOT NULL DEFAULT 0,
  `Job` int(2) NOT NULL DEFAULT 0,
  `Paycheck` int(4) NOT NULL DEFAULT 0,
  `HeadValue` int(3) NOT NULL DEFAULT 0,
  `Jailed` int(1) NOT NULL DEFAULT 0,
  `JailTime` int(3) NOT NULL DEFAULT 0,
  `Materials` int(3) NOT NULL DEFAULT 0,
  `Drugs` int(3) NOT NULL DEFAULT 0,
  `Leader` int(2) NOT NULL DEFAULT 0,
  `Member` int(2) NOT NULL DEFAULT 0,
  `FMember` int(3) NOT NULL DEFAULT 0,
  `Rank` int(3) NOT NULL DEFAULT 0,
  `Char` int(3) NOT NULL DEFAULT 0,
  `ContractTime` int(1) NOT NULL DEFAULT 0,
  `DetSkill` int(5) NOT NULL DEFAULT 0,
  `SexSkill` int(5) NOT NULL DEFAULT 0,
  `BoxSkill` int(5) NOT NULL DEFAULT 0,
  `LawSkill` int(5) NOT NULL DEFAULT 0,
  `MechSkill` int(5) NOT NULL DEFAULT 0,
  `JackSkill` int(5) NOT NULL DEFAULT 0,
  `CarSkill` int(5) NOT NULL DEFAULT 0,
  `NewsSkill` int(5) NOT NULL DEFAULT 0,
  `DrugsSkill` int(5) NOT NULL DEFAULT 0,
  `CookSkill` int(5) NOT NULL DEFAULT 0,
  `FishSkill` int(5) NOT NULL DEFAULT 0,
  `pSHealth` float NOT NULL,
  `pHealth` float NOT NULL,
  `Int` int(3) NOT NULL DEFAULT 0,
  `Local` int(3) NOT NULL DEFAULT 0,
  `Team` int(3) NOT NULL DEFAULT 0,
  `Model` int(3) NOT NULL DEFAULT 0,
  `PhoneNr` int(4) NOT NULL DEFAULT 0,
  `House` int(2) NOT NULL DEFAULT 0,
  `Bizz` int(2) NOT NULL DEFAULT 0,
  `Pos_x` float NOT NULL DEFAULT 0,
  `Pos_y` float NOT NULL DEFAULT 0,
  `Pos_z` float NOT NULL DEFAULT 0,
  `CarLic` int(1) NOT NULL DEFAULT 0,
  `FlyLic` int(1) NOT NULL DEFAULT 0,
  `BoatLic` int(1) NOT NULL DEFAULT 0,
  `FishLic` int(1) NOT NULL DEFAULT 0,
  `GunLic` int(1) NOT NULL DEFAULT 0,
  `Gun1` int(3) NOT NULL DEFAULT 0,
  `Gun2` int(3) NOT NULL DEFAULT 0,
  `Gun3` int(3) NOT NULL DEFAULT 0,
  `Gun4` int(3) NOT NULL DEFAULT 0,
  `Ammo1` int(3) NOT NULL DEFAULT 0,
  `Ammo2` int(3) NOT NULL DEFAULT 0,
  `Ammo3` int(3) NOT NULL DEFAULT 0,
  `Ammo4` int(3) NOT NULL DEFAULT 0,
  `CarTime` int(3) NOT NULL DEFAULT 0,
  `PayDay` int(5) NOT NULL DEFAULT 0,
  `PayDayHad` int(1) NOT NULL DEFAULT 0,
  `CDPlayer` int(1) NOT NULL DEFAULT 0,
  `Wins` int(3) NOT NULL DEFAULT 0,
  `Loses` int(3) NOT NULL DEFAULT 0,
  `AlcoholPerk` int(3) NOT NULL DEFAULT 0,
  `DrugPerk` int(3) NOT NULL DEFAULT 0,
  `MiserPerk` int(3) NOT NULL DEFAULT 0,
  `PainPerk` int(3) NOT NULL DEFAULT 0,
  `TraderPerk` int(3) NOT NULL DEFAULT 0,
  `Tutorial` int(1) NOT NULL DEFAULT 0,
  `Mission` int(3) NOT NULL DEFAULT 0,
  `Warnings` int(3) NOT NULL DEFAULT 0,
  `Adjustable` int(3) NOT NULL DEFAULT 0,
  `Fuel` int(3) NOT NULL DEFAULT 0,
  `Married` int(3) NOT NULL DEFAULT 0,
  `MarriedTo` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Characters`
--

INSERT INTO `Characters` (`ID`, `AID`, `Name`, `Date`, `Level`, `AdminLevel`, `DonateRank`, `UpgradePoints`, `ConnectedTime`, `Registered`, `Sex`, `Age`, `Continent`, `Origin`, `CK`, `Muted`, `Respect`, `Money`, `Bank`, `Crimes`, `Kills`, `Deaths`, `Arrested`, `WantedDeaths`, `Phonebook`, `LottoNr`, `Fishes`, `BiggestFish`, `Job`, `Paycheck`, `HeadValue`, `Jailed`, `JailTime`, `Materials`, `Drugs`, `Leader`, `Member`, `FMember`, `Rank`, `Char`, `ContractTime`, `DetSkill`, `SexSkill`, `BoxSkill`, `LawSkill`, `MechSkill`, `JackSkill`, `CarSkill`, `NewsSkill`, `DrugsSkill`, `CookSkill`, `FishSkill`, `pSHealth`, `pHealth`, `Int`, `Local`, `Team`, `Model`, `PhoneNr`, `House`, `Bizz`, `Pos_x`, `Pos_y`, `Pos_z`, `CarLic`, `FlyLic`, `BoatLic`, `FishLic`, `GunLic`, `Gun1`, `Gun2`, `Gun3`, `Gun4`, `Ammo1`, `Ammo2`, `Ammo3`, `Ammo4`, `CarTime`, `PayDay`, `PayDayHad`, `CDPlayer`, `Wins`, `Loses`, `AlcoholPerk`, `DrugPerk`, `MiserPerk`, `PainPerk`, `TraderPerk`, `Tutorial`, `Mission`, `Warnings`, `Adjustable`, `Fuel`, `Married`, `MarriedTo`) VALUES
(4, 14, 'Danny_Wolker', '24-03-2026', 1, 1338, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 13396, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4374, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 1318926876, 3, 291, 0, 255, 255, 2068.11, -1323.31, 23.8203, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'No-one'),
(6, 15, 'Luiz_Diaz', '27-03-2026', 1, 1338, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 6000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2103, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 0, 1318926876, 3, 291, 0, 255, 255, 214.499, -1524.86, 16.8468, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'No-one'),
(7, 15, 'Dupa_Dupa', '27-03-2026', 1, 0, 0, 0, 0, 1, 0, 25, 0, 0, 0, 0, 0, 6000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 255, 3, 291, 0, 255, 255, 2401.18, -1521.94, 23.8281, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'No-one'),
(8, 14, 'Kevin_Parkerson', '27-03-2026', 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 6770, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1808, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69, 0, 255, 3, 291, 0, 255, 255, 1995.44, -1175.16, 20.2474, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'No-one'),
(10, 15, 'AB_AB', '27-03-2026', 1, 0, 0, 0, 0, 1, 1, 26, 0, 0, 0, 0, 0, 6000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 255, 3, 93, 0, 255, 255, 2320.04, -1507.11, 26.8438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'No-one'),
(11, 14, 'Alex_Walker', '27-03-2026', 1, 0, 0, 0, 0, 1, 1, 30, 1, 0, 0, 0, 0, 6000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 98, 0, 255, 3, 93, 0, 255, 255, 2498.17, -1498.01, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'No-one'),
(12, 15, 'Dupaa_Dupaaa', '27-03-2026', 1, 0, 0, 0, 0, 1, 0, 34, 1, 0, 0, 0, 0, 6000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 255, 3, 291, 0, 255, 255, 2386.28, -1531.45, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'No-one');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Items`
--

CREATE TABLE `Items` (
  `ID` int(5) NOT NULL,
  `OwnerID` int(5) NOT NULL DEFAULT 0,
  `OwnerType` int(1) NOT NULL DEFAULT 0,
  `Name` varchar(64) NOT NULL DEFAULT 'Brak',
  `Type` int(2) NOT NULL DEFAULT 0,
  `SubType` int(2) NOT NULL DEFAULT 0,
  `Amount` int(9) NOT NULL DEFAULT 0,
  `Pos` varchar(32) NOT NULL DEFAULT '0.0,0.0,0.0',
  `Used` tinyint(1) NOT NULL DEFAULT 0,
  `Vw` int(5) NOT NULL DEFAULT 0,
  `Int` int(5) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Items`
--

INSERT INTO `Items` (`ID`, `OwnerID`, `OwnerType`, `Name`, `Type`, `SubType`, `Amount`, `Pos`, `Used`, `Vw`, `Int`) VALUES
(1, 4, 1, 'Chleb', 2, 3, 10, '0.0,0.0,0.0', 0, 0, 0);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `Vehicles`
--

CREATE TABLE `Vehicles` (
  `ID` int(5) NOT NULL,
  `OwnerID` int(5) NOT NULL DEFAULT 0,
  `OwnerType` int(1) NOT NULL DEFAULT 0,
  `BizID` int(5) NOT NULL DEFAULT 0,
  `AccessID` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `RentID` int(5) NOT NULL DEFAULT 0,
  `ModelID` int(3) NOT NULL DEFAULT 0,
  `EngineType` int(1) NOT NULL DEFAULT 0,
  `Color` varchar(8) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Pos` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Fuel` float NOT NULL DEFAULT 0,
  `Locked` tinyint(1) NOT NULL DEFAULT 0,
  `Engine` tinyint(1) NOT NULL DEFAULT 0,
  `EngineHp` float NOT NULL DEFAULT 0,
  `Spawned` tinyint(1) NOT NULL DEFAULT 0,
  `LightsOn` tinyint(1) NOT NULL DEFAULT 0,
  `Window` varchar(8) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Accessories` int(1) NOT NULL DEFAULT 0,
  `Panels` int(4) NOT NULL DEFAULT 0,
  `Doors` int(4) NOT NULL DEFAULT 0,
  `Lights` int(4) NOT NULL DEFAULT 0,
  `Tires` int(4) NOT NULL DEFAULT 0,
  `Vw` int(9) NOT NULL DEFAULT 0,
  `Int` int(9) NOT NULL DEFAULT 0,
  `Paintjob` int(1) NOT NULL DEFAULT 0,
  `Nitro` int(4) NOT NULL DEFAULT -1,
  `Components` varchar(82) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Repair` float NOT NULL DEFAULT 0,
  `Mileage` float NOT NULL DEFAULT 0,
  `Block` tinyint(1) NOT NULL DEFAULT 0,
  `Desc` varchar(128) NOT NULL DEFAULT 'Brak',
  `Plate` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `Vehicles`
--

INSERT INTO `Vehicles` (`ID`, `OwnerID`, `OwnerType`, `BizID`, `AccessID`, `RentID`, `ModelID`, `EngineType`, `Color`, `Pos`, `Fuel`, `Locked`, `Engine`, `EngineHp`, `Spawned`, `LightsOn`, `Window`, `Accessories`, `Panels`, `Doors`, `Lights`, `Tires`, `Vw`, `Int`, `Paintjob`, `Nitro`, `Components`, `Repair`, `Mileage`, `Block`, `Desc`, `Plate`) VALUES
(1, 0, 0, 0, 'Brak', 0, 572, 0, '-1,-1', '1359.989257,-1962.840332,31.553', 59.1041, 0, 0, 1000, 1, 0, 'Brak', 0, 0, 0, 0, 0, 0, 0, 0, -1, 'Brak', 0, 1.21429, 0, '  ', ' '),
(2, 0, 0, 0, 'Brak', 0, 572, 0, '-1,-1', '1194.536376,-2059.369384,68.580', 59.3771, 0, 1, 1000, 1, 0, 'Brak', 0, 0, 0, 0, 0, 0, 0, 0, -1, 'Brak', 0, 0.811428, 0, '  ', ' '),
(3, 0, 0, 0, 'Brak', 0, 572, 0, '-1,-1', '1160.934936,-2050.528320,68.584', 59.0882, 0, 1, 1000, 1, 0, 'Brak', 0, 0, 0, 0, 0, 0, 0, 0, -1, 'Brak', 0, 0.962857, 0, '  ', ' '),
(4, 0, 0, 0, 'Brak', 0, 572, 0, '-1,-1', '1249.468627,-2043.118774,59.298', 60, 0, 0, 1000, 1, 0, 'Brak', 0, 0, 0, 0, 0, 0, 0, 0, -1, 'Brak', 0, 0, 0, '  ', ' '),
(5, 0, 0, 0, 'Brak', 0, 572, 0, '-1,-1', '1251.9773, -2043.0979, 59.3744', 60, 0, 0, 2000, 1, 0, 'Brak', 0, 0, 0, 0, 0, 0, 0, 0, -1, 'Brak', 0, 0, 0, '  ', ' '),
(6, 0, 0, 0, 'Brak', 0, 572, 0, '-1,-1', '1255.971557,-2043.505004,59.109', 59.1032, 0, 0, 951.264, 1, 0, 'Brak', 0, 0, 0, 0, 0, 0, 0, 0, -1, 'Brak', 0, 1.29143, 0, '  ', ' '),
(7, 4, 1, 0, 'Brak', 0, 585, 0, '3,4', '1357.968383,-1109.056396,23.372', 54.6222, 0, 1, 1924.08, 1, 0, 'Brak', 0, 1048592, 33554432, 4, 0, 0, 0, 0, -1, 'Brak', 0, 7.34, 0, 'Brak', 'Brak');

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `Accounts`
--
ALTER TABLE `Accounts`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `Characters`
--
ALTER TABLE `Characters`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `AID` (`AID`);

--
-- Indeksy dla tabeli `Items`
--
ALTER TABLE `Items`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `Vehicles`
--
ALTER TABLE `Vehicles`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Accounts`
--
ALTER TABLE `Accounts`
  MODIFY `ID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `Characters`
--
ALTER TABLE `Characters`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT for table `Items`
--
ALTER TABLE `Items`
  MODIFY `ID` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `Characters`
--
ALTER TABLE `Characters`
  ADD CONSTRAINT `Characters_ibfk_1` FOREIGN KEY (`AID`) REFERENCES `Accounts` (`ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
