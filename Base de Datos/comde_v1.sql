-- MariaDB dump 10.17  Distrib 10.4.8-MariaDB, for Win64 (AMD64)
--
-- Host: localhost    Database: comde
-- ------------------------------------------------------
-- Server version	10.4.8-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `alumno`
--

DROP TABLE IF EXISTS `alumno`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alumno` (
  `idAlumno` varchar(35) NOT NULL,
  `nombreAlumno` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `claveEstado` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL,
  PRIMARY KEY (`idAlumno`),
  KEY `idCurso` (`idCurso`),
  KEY `idArea` (`idArea`),
  KEY `claveEstado` (`claveEstado`),
  KEY `idSeccion` (`idSeccion`),
  CONSTRAINT `alumno_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `alumno_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`),
  CONSTRAINT `alumno_ibfk_3` FOREIGN KEY (`claveEstado`) REFERENCES `estado` (`claveEstado`),
  CONSTRAINT `alumno_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `alumno`
--

LOCK TABLES `alumno` WRITE;
/*!40000 ALTER TABLE `alumno` DISABLE KEYS */;
/*!40000 ALTER TABLE `alumno` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `area_deportiva`
--

DROP TABLE IF EXISTS `area_deportiva`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `area_deportiva` (
  `idArea` int(11) NOT NULL,
  `nombreArea` varchar(50) NOT NULL,
  PRIMARY KEY (`idArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `area_deportiva`
--

LOCK TABLES `area_deportiva` WRITE;
/*!40000 ALTER TABLE `area_deportiva` DISABLE KEYS */;
/*!40000 ALTER TABLE `area_deportiva` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `curso`
--

DROP TABLE IF EXISTS `curso`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `curso` (
  `idCurso` int(11) NOT NULL,
  `matriculaProfesor` varchar(35) NOT NULL,
  `idHorario` int(11) NOT NULL,
  `idLocacion` int(11) NOT NULL,
  `idSeccion` int(11) NOT NULL,
  PRIMARY KEY (`idCurso`),
  KEY `matriculaProfesor` (`matriculaProfesor`),
  KEY `idHorario` (`idHorario`),
  KEY `idLocacion` (`idLocacion`),
  KEY `idSeccion` (`idSeccion`),
  CONSTRAINT `curso_ibfk_1` FOREIGN KEY (`matriculaProfesor`) REFERENCES `trabajador` (`matricula`),
  CONSTRAINT `curso_ibfk_2` FOREIGN KEY (`idHorario`) REFERENCES `horario` (`idHorario`),
  CONSTRAINT `curso_ibfk_3` FOREIGN KEY (`idLocacion`) REFERENCES `locacion` (`idLocacion`),
  CONSTRAINT `curso_ibfk_4` FOREIGN KEY (`idSeccion`) REFERENCES `seccion` (`idSeccion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `curso`
--

LOCK TABLES `curso` WRITE;
/*!40000 ALTER TABLE `curso` DISABLE KEYS */;
/*!40000 ALTER TABLE `curso` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `curso_abierto`
--

DROP TABLE IF EXISTS `curso_abierto`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `curso_abierto` (
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  `nombreCurso` varchar(45) NOT NULL,
  KEY `idCurso` (`idCurso`),
  KEY `idArea` (`idArea`),
  CONSTRAINT `curso_abierto_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `curso_abierto_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `curso_abierto`
--

LOCK TABLES `curso_abierto` WRITE;
/*!40000 ALTER TABLE `curso_abierto` DISABLE KEYS */;
/*!40000 ALTER TABLE `curso_abierto` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `estado`
--

DROP TABLE IF EXISTS `estado`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `estado` (
  `claveEstado` int(11) NOT NULL,
  `descripcionEstado` varchar(50) NOT NULL,
  PRIMARY KEY (`claveEstado`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `estado`
--

LOCK TABLES `estado` WRITE;
/*!40000 ALTER TABLE `estado` DISABLE KEYS */;
/*!40000 ALTER TABLE `estado` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `horario`
--

DROP TABLE IF EXISTS `horario`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `horario` (
  `idHorario` int(11) NOT NULL,
  `hora_inicio` time NOT NULL,
  `hora_final` time NOT NULL,
  PRIMARY KEY (`idHorario`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `horario`
--

LOCK TABLES `horario` WRITE;
/*!40000 ALTER TABLE `horario` DISABLE KEYS */;
/*!40000 ALTER TABLE `horario` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `locacion`
--

DROP TABLE IF EXISTS `locacion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `locacion` (
  `idLocacion` int(11) NOT NULL,
  `lugar` varchar(50) NOT NULL,
  PRIMARY KEY (`idLocacion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `locacion`
--

LOCK TABLES `locacion` WRITE;
/*!40000 ALTER TABLE `locacion` DISABLE KEYS */;
/*!40000 ALTER TABLE `locacion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nivel_trabajador`
--

DROP TABLE IF EXISTS `nivel_trabajador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `nivel_trabajador` (
  `nivelTrabajador` int(11) NOT NULL,
  `puesto` varchar(50) NOT NULL,
  PRIMARY KEY (`nivelTrabajador`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nivel_trabajador`
--

LOCK TABLES `nivel_trabajador` WRITE;
/*!40000 ALTER TABLE `nivel_trabajador` DISABLE KEYS */;
/*!40000 ALTER TABLE `nivel_trabajador` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `profesor`
--

DROP TABLE IF EXISTS `profesor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `profesor` (
  `matricula` varchar(35) NOT NULL,
  `idCurso` int(11) NOT NULL,
  `idArea` int(11) NOT NULL,
  PRIMARY KEY (`matricula`),
  KEY `idCurso` (`idCurso`),
  KEY `idArea` (`idArea`),
  CONSTRAINT `profesor_ibfk_1` FOREIGN KEY (`idCurso`) REFERENCES `curso` (`idCurso`),
  CONSTRAINT `profesor_ibfk_2` FOREIGN KEY (`idArea`) REFERENCES `area_deportiva` (`idArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `profesor`
--

LOCK TABLES `profesor` WRITE;
/*!40000 ALTER TABLE `profesor` DISABLE KEYS */;
/*!40000 ALTER TABLE `profesor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `seccion`
--

DROP TABLE IF EXISTS `seccion`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `seccion` (
  `idSeccion` int(11) NOT NULL,
  `descripcion` varchar(250) NOT NULL,
  PRIMARY KEY (`idSeccion`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `seccion`
--

LOCK TABLES `seccion` WRITE;
/*!40000 ALTER TABLE `seccion` DISABLE KEYS */;
/*!40000 ALTER TABLE `seccion` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trabajador`
--

DROP TABLE IF EXISTS `trabajador`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trabajador` (
  `matricula` varchar(35) NOT NULL,
  `nombre` varchar(35) NOT NULL,
  `apellidoP` varchar(35) NOT NULL,
  `apellidoM` varchar(35) NOT NULL,
  `correoE` varchar(60) NOT NULL,
  `celular` varchar(13) DEFAULT NULL,
  `edad` int(11) NOT NULL,
  `contrasegna` varchar(30) NOT NULL,
  `nivel` int(11) NOT NULL,
  PRIMARY KEY (`matricula`),
  KEY `nivel` (`nivel`),
  CONSTRAINT `trabajador_ibfk_1` FOREIGN KEY (`nivel`) REFERENCES `nivel_trabajador` (`nivelTrabajador`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trabajador`
--

LOCK TABLES `trabajador` WRITE;
/*!40000 ALTER TABLE `trabajador` DISABLE KEYS */;
/*!40000 ALTER TABLE `trabajador` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-10-17 11:57:30
