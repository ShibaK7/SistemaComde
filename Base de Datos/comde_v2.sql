-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 10-11-2019 a las 06:59:57
-- Versión del servidor: 10.1.29-MariaDB
-- Versión de PHP: 7.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `comde`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `alumno`
--

CREATE TABLE `alumno` (
  `idAlumno` varchar(35) NOT NULL,
  `nombreAlumno` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `claveEstado` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `area_deportiva`
--

CREATE TABLE `area_deportiva` (
  `idArea` int(11) NOT NULL,
  `nombreArea` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `area_deportiva`
--

INSERT INTO `area_deportiva` (`idArea`, `nombreArea`) VALUES
(1, 'Deportes de Combate'),
(2, 'Escuela de Gimnasia'),
(3, 'Centro Acuatico');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `curso`
--

CREATE TABLE `curso` (
  `idCurso` int(11) NOT NULL,
  `matriculaProfesor` varchar(35) NOT NULL,
  `idHorario` int(11) NOT NULL,
  `idLocacion` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `curso`
--

INSERT INTO `curso` (`idCurso`, `matriculaProfesor`, `idHorario`, `idLocacion`, `idSeccion`) VALUES
(1, '100034438', 1, 1, 1),
(2, '100034439', 2, 3, 2),
(3, '100034437', 1, 3, 1),
(4, '100034440', 2, 2, 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `curso_abierto`
--

CREATE TABLE `curso_abierto` (
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `nombreCurso` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `curso_abierto`
--

INSERT INTO `curso_abierto` (`idCurso`, `idArea`, `nombreCurso`) VALUES
(1, 1, 'Karate Do'),
(2, 2, 'Gimnasia Infantil'),
(3, 3, 'Natacion para principiantes'),
(4, 3, 'Natacion Avanzada');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `estado`
--

CREATE TABLE `estado` (
  `claveEstado` int(11) NOT NULL,
  `descripcionEstado` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `horario`
--

CREATE TABLE `horario` (
  `idHorario` int(11) NOT NULL,
  `hora_inicio` time NOT NULL,
  `hora_final` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `horario`
--

INSERT INTO `horario` (`idHorario`, `hora_inicio`, `hora_final`) VALUES
(1, '09:00:00', '11:00:00'),
(2, '11:00:00', '12:00:00');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `locacion`
--

CREATE TABLE `locacion` (
  `idLocacion` int(11) NOT NULL,
  `lugar` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `locacion`
--

INSERT INTO `locacion` (`idLocacion`, `lugar`) VALUES
(1, 'Dojo Karate COMDE'),
(2, 'Centro Acuatico COMDE'),
(3, 'Centro de Gimnasia COMDE');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `nivel_trabajador`
--

CREATE TABLE `nivel_trabajador` (
  `nivelTrabajador` int(11) NOT NULL,
  `puesto` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `nivel_trabajador`
--

INSERT INTO `nivel_trabajador` (`nivelTrabajador`, `puesto`) VALUES
(1, 'Administrador General'),
(2, 'Administrador de Area'),
(3, 'Profesor');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `profesor`
--

CREATE TABLE `profesor` (
  `matricula` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `seccion`
--

CREATE TABLE `seccion` (
  `idSeccion` int(11) NOT NULL,
  `descripcion` varchar(250) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `seccion`
--

INSERT INTO `seccion` (`idSeccion`, `descripcion`) VALUES
(1, 'Seccion 1'),
(2, 'Seccion 2');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `trabajador`
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
-- Volcado de datos para la tabla `trabajador`
--

INSERT INTO `trabajador` (`matricula`, `nombre`, `apellidoP`, `apellidoM`, `correoE`, `celular`, `edad`, `contrasegna`, `nivel`) VALUES
('100034433', 'Esteban', 'Calixto', 'Cruz', 'esteban_calixto_cruz4@hotmail.com', '2321259246', 25, '1728', 1),
('100034434', 'Sandra', 'Rosas', 'Ortega', 'sandra@gmail.com', '2321259247', 25, '12345', 2),
('100034435', 'Jiuber', 'Monfil', 'Quijano', 'Jiuber@gmail.com', '2321259248', 25, '12345', 2),
('100034436', 'Juan ', 'Flores ', 'Cabañas', 'Juanpi@hotmail.com', '2321259249', 25, '12345', 2),
('100034437', 'Jorge', 'Lopez', 'Aragon', 'Alucard@gmail.com', '2321259250', 25, '12345', 3),
('100034438', 'Laura', 'Villarreal ', 'Onofre', 'lauraV@gmail.com', '2321259251', 25, '12345', 3),
('100034439', 'Yecxalin', 'Cobos', 'Tejeda', 'yecxa@hotmail.com', '2321259252', 25, '12345', 3),
('100034440', 'Carla', 'Sofia', 'Alarcon', 'Santiago@hotmail.com', '2321259253', 25, '12345', 3),
('100034441', 'Juan', 'Luna', 'Ojeda', 'luna@hotmail.com', '2321259253', 25, '12345', 3),
('100034442', 'Ana', 'Julian', 'Garcia', 'acuario@gmail.com', '2321259254', 25, '12345', 3),
('100034443', 'Jorge', 'Hernandez', 'Baltazar', 'jHernandez@gmail.com', '2321259255', 25, '12345', 3),
('100034444', 'Hector', 'Celis', 'Cabrera', 'hectorM@hotmail.com', '2321259256', 25, '12345', 3),
('100034445', 'Bryan', 'Celis', 'Cabrera', 'bryan@gmail.com', '2321259257', 25, '12345', 3);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `alumno`
--
ALTER TABLE `alumno`
  ADD PRIMARY KEY (`idAlumno`),
  ADD KEY `idCurso` (`idCurso`),
  ADD KEY `idArea` (`idArea`),
  ADD KEY `claveEstado` (`claveEstado`),
  ADD KEY `idSeccion` (`idSeccion`);

--
-- Indices de la tabla `area_deportiva`
--
ALTER TABLE `area_deportiva`
  ADD PRIMARY KEY (`idArea`);

--
-- Indices de la tabla `curso`
--
ALTER TABLE `curso`
  ADD PRIMARY KEY (`idCurso`),
  ADD KEY `matriculaProfesor` (`matriculaProfesor`),
  ADD KEY `idHorario` (`idHorario`),
  ADD KEY `idLocacion` (`idLocacion`),
  ADD KEY `idSeccion` (`idSeccion`);

--
-- Indices de la tabla `curso_abierto`
--
ALTER TABLE `curso_abierto`
  ADD KEY `idCurso` (`idCurso`),
  ADD KEY `idArea` (`idArea`);

--
-- Indices de la tabla `estado`
--
ALTER TABLE `estado`
  ADD PRIMARY KEY (`claveEstado`);

--
-- Indices de la tabla `horario`
--
ALTER TABLE `horario`
  ADD PRIMARY KEY (`idHorario`);

--
-- Indices de la tabla `locacion`
--
ALTER TABLE `locacion`
  ADD PRIMARY KEY (`idLocacion`);

--
-- Indices de la tabla `nivel_trabajador`
--
ALTER TABLE `nivel_trabajador`
  ADD PRIMARY KEY (`nivelTrabajador`);

--
-- Indices de la tabla `profesor`
--
ALTER TABLE `profesor`
  ADD PRIMARY KEY (`matricula`),
  ADD KEY `idCurso` (`idCurso`),
  ADD KEY `idArea` (`idArea`);

--
-- Indices de la tabla `seccion`
--
ALTER TABLE `seccion`
  ADD PRIMARY KEY (`idSeccion`);

--
-- Indices de la tabla `trabajador`
--
ALTER TABLE `trabajador`
  ADD PRIMARY KEY (`matricula`),
  ADD KEY `nivel` (`nivel`);

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `alumno`
--
ALTER TABLE `alumno`
  ADD CONSTRAINT `alumno_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `alumno_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`),
  ADD CONSTRAINT `alumno_ibfk_3` FOREIGN KEY (`claveEstado`) REFERENCES `estado` (`claveEstado`),
  ADD CONSTRAINT `alumno_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`);

--
-- Filtros para la tabla `curso`
--
ALTER TABLE `curso`
  ADD CONSTRAINT `curso_ibfk_1` FOREIGN KEY (`matriculaProfesor`) REFERENCES `trabajador` (`matricula`),
  ADD CONSTRAINT `curso_ibfk_2` FOREIGN KEY (`idHorario`) REFERENCES `horario` (`idHorario`),
  ADD CONSTRAINT `curso_ibfk_3` FOREIGN KEY (`idLocacion`) REFERENCES `locacion` (`idLocacion`),
  ADD CONSTRAINT `curso_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`);

--
-- Filtros para la tabla `curso_abierto`
--
ALTER TABLE `curso_abierto`
  ADD CONSTRAINT `curso_abierto_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `curso_abierto_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`);

--
-- Filtros para la tabla `profesor`
--
ALTER TABLE `profesor`
  ADD CONSTRAINT `profesor_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  ADD CONSTRAINT `profesor_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`);

--
-- Filtros para la tabla `trabajador`
--
ALTER TABLE `trabajador`
  ADD CONSTRAINT `trabajador_ibfk_1` FOREIGN KEY (`nivel`) REFERENCES `nivel_trabajador` (`nivelTrabajador`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
