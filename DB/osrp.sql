-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Paź 09, 2026 at 04:08 PM
-- Wersja serwera: 10.4.32-MariaDB
-- Wersja PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `osrp`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `accounts`
--

CREATE TABLE `accounts` (
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

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `characters`
--

CREATE TABLE `characters` (
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

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `items`
--

CREATE TABLE `items` (
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

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `plants`
--

CREATE TABLE `plants` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) NOT NULL,
  `PosX` float NOT NULL,
  `PosY` float NOT NULL,
  `PosZ` float NOT NULL,
  `RotZ` float NOT NULL DEFAULT 0,
  `Grown` int(11) NOT NULL DEFAULT 0,
  `WateredUntil` int(11) NOT NULL DEFAULT 0,
  `LastUpdate` int(11) NOT NULL DEFAULT 0,
  `Planted` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `vehicles`
--

CREATE TABLE `vehicles` (
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
  `Plate` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Brak',
  `Desc` varchar(128) NOT NULL DEFAULT 'Brak'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `AID` (`AID`);

--
-- Indeksy dla tabeli `items`
--
ALTER TABLE `items`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `plants`
--
ALTER TABLE `plants`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `OwnerID` (`OwnerID`);

--
-- Indeksy dla tabeli `vehicles`
--
ALTER TABLE `vehicles`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `accounts`
--
ALTER TABLE `accounts`
  MODIFY `ID` int(3) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `items`
--
ALTER TABLE `items`
  MODIFY `ID` int(5) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `plants`
--
ALTER TABLE `plants`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `vehicles`
--
ALTER TABLE `vehicles`
  MODIFY `ID` int(5) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `characters`
--
ALTER TABLE `characters`
  ADD CONSTRAINT `Characters_ibfk_1` FOREIGN KEY (`AID`) REFERENCES `accounts` (`ID`);

--
-- Constraints for table `plants`
--
ALTER TABLE `plants`
  ADD CONSTRAINT `Trees_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `characters` (`ID`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
