-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 11, 2019 at 06:49 PM
-- Server version: 10.1.29-MariaDB
-- PHP Version: 7.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `basecalidad`
--

-- --------------------------------------------------------

--
-- Table structure for table `alumno`
--

CREATE TABLE `alumno` (
  `idAlumno` int(11) NOT NULL,
  `nombreAlumno` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `claveEstado` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `alumno`
--

INSERT INTO `alumno` (`idAlumno`, `nombreAlumno`, `apellidoP`, `apellidoM`, `idCurso`, `idArea`, `claveEstado`, `idSeccion`) VALUES
(1, 'Jorge', 'Molina', 'Lechuga', 1, 1, 1, 1),
(2, 'Oliver', 'Viveroz', 'Juárez', 2, 2, 1, 1),
(3, 'Tony', 'Paniagua', 'Ramos', 3, 1, 1, 1),
(4, 'esteban', 'ghi', 'ghi', 4, 1, 1, 1),
(5, 'dana', 'jkl', 'jkl', 5, 1, 1, 1),
(6, 'Luis Angel', 'Amador', 'Ortiz', 6, 1, 1, 1),
(7, 'Isma', 'Mendez', 'Suarez', 5, 1, 1, 1),
(8, 'Isma', 'Mendez', 'Suarez', 6, 1, 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `area_deportiva`
--

CREATE TABLE `area_deportiva` (
  `idArea` int(11) NOT NULL,
  `nombreArea` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `area_deportiva`
--

INSERT INTO `area_deportiva` (`idArea`, `nombreArea`) VALUES
(1, 'Area 1'),
(2, 'area 2');

-- --------------------------------------------------------

--
-- Table structure for table `asistencia`
--

CREATE TABLE `asistencia` (
  `asisID` int(11) NOT NULL,
  `alumnoID` int(11) NOT NULL,
  `cursoID` int(11) NOT NULL,
  `horarioID` int(11) NOT NULL,
  `fecha` date DEFAULT NULL,
  `presente` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `asistencia`
--

INSERT INTO `asistencia` (`asisID`, `alumnoID`, `cursoID`, `horarioID`, `fecha`, `presente`) VALUES
(1, 1, 1, 1, '2019-10-23', 1),
(2, 2, 1, 1, '2019-10-23', 1),
(3, 3, 1, 1, '2019-10-23', 0),
(4, 4, 1, 1, '2019-10-23', 0),
(5, 5, 1, 1, '2019-10-23', 1),
(6, 6, 6, 6, '2019-10-23', 1);

-- --------------------------------------------------------

--
-- Table structure for table `curso`
--

CREATE TABLE `curso` (
  `idCurso` int(11) NOT NULL,
  `matriculaProfesor` varchar(35) NOT NULL,
  `idHorario` int(11) NOT NULL,
  `idLocacion` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `curso`
--

INSERT INTO `curso` (`idCurso`, `matriculaProfesor`, `idHorario`, `idLocacion`, `idSeccion`) VALUES
(1, '12345', 1, 1, 1),
(2, '12345', 2, 1, 1),
(3, '12345', 3, 1, 1),
(4, '12345', 4, 1, 1),
(5, '12345', 5, 1, 1),
(6, '12345', 6, 1, 1);

-- --------------------------------------------------------

--
-- Table structure for table `curso_abierto`
--

CREATE TABLE `curso_abierto` (
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `nombreCurso` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `curso_abierto`
--

INSERT INTO `curso_abierto` (`idCurso`, `idArea`, `nombreCurso`) VALUES
(1, 1, 'clase futbol'),
(1, 1, 'clase basebal'),
(1, 1, 'clase atletismo'),
(2, 1, 'fut 2'),
(3, 1, 'curso 3'),
(4, 1, 'curso 4'),
(5, 1, 'curso 5'),
(6, 1, 'curso 6');

-- --------------------------------------------------------

--
-- Table structure for table `estado`
--

CREATE TABLE `estado` (
  `claveEstado` int(11) NOT NULL,
  `descripcionEstado` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `estado`
--

INSERT INTO `estado` (`claveEstado`, `descripcionEstado`) VALUES
(1, 'activo');

-- --------------------------------------------------------

--
-- Table structure for table `horario`
--

CREATE TABLE `horario` (
  `idHorario` int(11) NOT NULL,
  `hora_inicio` time NOT NULL,
  `hora_final` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `horario`
--

INSERT INTO `horario` (`idHorario`, `hora_inicio`, `hora_final`) VALUES
(1, '00:00:00', '03:59:59'),
(2, '04:00:00', '07:59:59'),
(3, '08:00:00', '11:59:59'),
(4, '12:00:00', '15:59:59'),
(5, '16:00:00', '19:59:59'),
(6, '20:00:00', '24:59:59');

-- --------------------------------------------------------

--
-- Table structure for table `locacion`
--

CREATE TABLE `locacion` (
  `idLocacion` int(11) NOT NULL,
  `lugar` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `locacion`
--

INSERT INTO `locacion` (`idLocacion`, `lugar`) VALUES
(1, 'Gimnasio');

-- --------------------------------------------------------

--
-- Table structure for table `nivel_trabajador`
--

CREATE TABLE `nivel_trabajador` (
  `nivelTrabajador` int(11) NOT NULL,
  `puesto` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `nivel_trabajador`
--

INSERT INTO `nivel_trabajador` (`nivelTrabajador`, `puesto`) VALUES
(1, 'jefe');

-- --------------------------------------------------------

--
-- Table structure for table `profesor`
--

CREATE TABLE `profesor` (
  `matricula` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `seccion`
--

CREATE TABLE `seccion` (
  `idSeccion` int(11) NOT NULL,
  `descripcion` varchar(250) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `seccion`
--

INSERT INTO `seccion` (`idSeccion`, `descripcion`) VALUES
(1, 'Primer grupo');

-- --------------------------------------------------------

--
-- Table structure for table `trabajador`
--

CREATE TABLE `trabajador` (
  `matricula` varchar(35) NOT NULL,
  `nombre` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `correoE` varchar(60) NOT NULL,
  `celular` varchar(13) DEFAULT NULL,
  `edad` int(11) NOT NULL,
  `contrasegna` varchar(30) NOT NULL,
  `nivel` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `trabajador`
--

INSERT INTO `trabajador` (`matricula`, `nombre`, `apellidoP`, `apellidoM`, `correoE`, `celular`, `edad`, `contrasegna`, `nivel`) VALUES
('12345', 'tony', 'paniagua', 'ramos', 'tony@gmail.com', '2229200704', 22, '123', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `alumno`
--
ALTER TABLE `alumno`
  ADD PRIMARY KEY (`idAlumno`),
  ADD KEY `idCurso` (`idCurso`),
  ADD KEY `idArea` (`idArea`),
  ADD KEY `claveEstado` (`claveEstado`),
  ADD KEY `idSeccion` (`idSeccion`);

--
-- Indexes for table `area_deportiva`
--
ALTER TABLE `area_deportiva`
  ADD PRIMARY KEY (`idArea`);

--
-- Indexes for table `asistencia`
--
ALTER TABLE `asistencia`
  ADD PRIMARY KEY (`asisID`),
  ADD KEY `alumnoID` (`alumnoID`),
  ADD KEY `cursoID` (`cursoID`),
  ADD KEY `horarioID` (`horarioID`);

--
-- Indexes for table `curso`
--
ALTER TABLE `curso`
  ADD PRIMARY KEY (`idCurso`),
  ADD KEY `matriculaProfesor` (`matriculaProfesor`),
  ADD KEY `idHorario` (`idHorario`),
  ADD KEY `idLocacion` (`idLocacion`),
  ADD KEY `idSeccion` (`idSeccion`);

--
-- Indexes for table `curso_abierto`
--
ALTER TABLE `curso_abierto`
  ADD KEY `idCurso` (`idCurso`),
  ADD KEY `idArea` (`idArea`);

--
-- Indexes for table `estado`
--
ALTER TABLE `estado`
  ADD PRIMARY KEY (`claveEstado`);

--
-- Indexes for table `horario`
--
ALTER TABLE `horario`
  ADD PRIMARY KEY (`idHorario`);

--
-- Indexes for table `locacion`
--
ALTER TABLE `locacion`
  ADD PRIMARY KEY (`idLocacion`);

--
-- Indexes for table `nivel_trabajador`
--
ALTER TABLE `nivel_trabajador`
  ADD PRIMARY KEY (`nivelTrabajador`);

--
-- Indexes for table `profesor`
--
ALTER TABLE `profesor`
  ADD PRIMARY KEY (`matricula`),
  ADD KEY `idCurso` (`idCurso`),
  ADD KEY `idArea` (`idArea`);

--
-- Indexes for table `seccion`
--
ALTER TABLE `seccion`
  ADD PRIMARY KEY (`idSeccion`);

--
-- Indexes for table `trabajador`
--
ALTER TABLE `trabajador`
  ADD PRIMARY KEY (`matricula`),
  ADD KEY `nivel` (`nivel`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `asistencia`
--
ALTER TABLE `asistencia`
  MODIFY `asisID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `alumno`
--
ALTER TABLE `alumno`
  ADD CONSTRAINT `alumno_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `alumno_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`),
  ADD CONSTRAINT `alumno_ibfk_3` FOREIGN KEY (`claveEstado`) REFERENCES `estado` (`claveEstado`),
  ADD CONSTRAINT `alumno_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`);

--
-- Constraints for table `asistencia`
--
ALTER TABLE `asistencia`
  ADD CONSTRAINT `asistencia_ibfk_1` FOREIGN KEY (`alumnoID`) REFERENCES `alumno` (`idAlumno`),
  ADD CONSTRAINT `asistencia_ibfk_2` FOREIGN KEY (`cursoID`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `asistencia_ibfk_3` FOREIGN KEY (`horarioID`) REFERENCES `horario` (`idHorario`);

--
-- Constraints for table `curso`
--
ALTER TABLE `curso`
  ADD CONSTRAINT `curso_ibfk_1` FOREIGN KEY (`matriculaProfesor`) REFERENCES `trabajador` (`matricula`),
  ADD CONSTRAINT `curso_ibfk_2` FOREIGN KEY (`idHorario`) REFERENCES `horario` (`idHorario`),
  ADD CONSTRAINT `curso_ibfk_3` FOREIGN KEY (`idLocacion`) REFERENCES `locacion` (`idLocacion`),
  ADD CONSTRAINT `curso_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`);

--
-- Constraints for table `curso_abierto`
--
ALTER TABLE `curso_abierto`
  ADD CONSTRAINT `curso_abierto_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `curso_abierto_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`);

--
-- Constraints for table `profesor`
--
ALTER TABLE `profesor`
  ADD CONSTRAINT `profesor_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `profesor_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`);

--
-- Constraints for table `trabajador`
--
ALTER TABLE `trabajador`
  ADD CONSTRAINT `trabajador_ibfk_1` FOREIGN KEY (`nivel`) REFERENCES `nivel_trabajador` (`nivelTrabajador`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
