EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:AudioJack2 J?
U 1 1 5FE9396A
P 4700 1600
AR Path="/5FE9396A" Ref="J?"  Part="1" 
AR Path="/5FE79040/5FE9396A" Ref="JackCV1"  Part="1" 
F 0 "JackCV1" H 4520 1583 50  0000 R CNN
F 1 "AudioJack2" H 4520 1674 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_Ledino_KB3SPRS_Horizontal" H 4700 1600 50  0001 C CNN
F 3 "~" H 4700 1600 50  0001 C CNN
	1    4700 1600
	-1   0    0    1   
$EndComp
$Comp
L Connector:AudioJack2 J?
U 1 1 5FE93970
P 4700 2150
AR Path="/5FE93970" Ref="J?"  Part="1" 
AR Path="/5FE79040/5FE93970" Ref="JackCV2"  Part="1" 
F 0 "JackCV2" H 4520 2133 50  0000 R CNN
F 1 "AudioJack2" H 4520 2224 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_Ledino_KB3SPRS_Horizontal" H 4700 2150 50  0001 C CNN
F 3 "~" H 4700 2150 50  0001 C CNN
	1    4700 2150
	-1   0    0    1   
$EndComp
$Comp
L Connector:AudioJack2 J?
U 1 1 5FE93976
P 4700 2750
AR Path="/5FE93976" Ref="J?"  Part="1" 
AR Path="/5FE79040/5FE93976" Ref="JackCV3"  Part="1" 
F 0 "JackCV3" H 4520 2733 50  0000 R CNN
F 1 "AudioJack2" H 4520 2824 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_Ledino_KB3SPRS_Horizontal" H 4700 2750 50  0001 C CNN
F 3 "~" H 4700 2750 50  0001 C CNN
	1    4700 2750
	-1   0    0    1   
$EndComp
$Comp
L Connector:AudioJack2 J?
U 1 1 5FE9397C
P 4700 3400
AR Path="/5FE9397C" Ref="J?"  Part="1" 
AR Path="/5FE79040/5FE9397C" Ref="JackGATE1"  Part="1" 
F 0 "JackGATE1" H 4520 3383 50  0000 R CNN
F 1 "AudioJack2" H 4520 3474 50  0000 R CNN
F 2 "Connector_Audio:Jack_3.5mm_Ledino_KB3SPRS_Horizontal" H 4700 3400 50  0001 C CNN
F 3 "~" H 4700 3400 50  0001 C CNN
	1    4700 3400
	-1   0    0    1   
$EndComp
$Comp
L Device:LED_Dual_2pin D?
U 1 1 5FE93982
P 4750 4050
AR Path="/5FE93982" Ref="D?"  Part="1" 
AR Path="/5FD0E1E1/5FE93982" Ref="D?"  Part="1" 
AR Path="/5FE79040/5FE93982" Ref="D1"  Part="1" 
F 0 "D1" H 4750 4446 50  0000 C CNN
F 1 "Gate LED" H 4750 4355 50  0000 C CNN
F 2 "" H 4750 4050 50  0001 C CNN
F 3 "~" H 4750 4050 50  0001 C CNN
	1    4750 4050
	0    1    1    0   
$EndComp
$Comp
L Connector:USB_A J?
U 1 1 5FE93988
P 9450 2350
AR Path="/5FE93988" Ref="J?"  Part="1" 
AR Path="/5FD0E1E1/5FE93988" Ref="J?"  Part="1" 
AR Path="/5FE79040/5FE93988" Ref="J7"  Part="1" 
F 0 "J7" H 9507 2817 50  0000 C CNN
F 1 "USB_A" H 9507 2726 50  0000 C CNN
F 2 "" H 9600 2300 50  0001 C CNN
F 3 " ~" H 9600 2300 50  0001 C CNN
	1    9450 2350
	-1   0    0    1   
$EndComp
$Comp
L Device:LED_Dual_2pin D?
U 1 1 5FE9398E
P 9450 3300
AR Path="/5FE9398E" Ref="D?"  Part="1" 
AR Path="/5FCAFED4/5FE9398E" Ref="D?"  Part="1" 
AR Path="/5FE79040/5FE9398E" Ref="D2"  Part="1" 
F 0 "D2" H 9450 3696 50  0000 C CNN
F 1 "USB Indicator Dual LED" H 9450 3605 50  0000 C CNN
F 2 "" H 9450 3300 50  0001 C CNN
F 3 "~" H 9450 3300 50  0001 C CNN
	1    9450 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9450 3600 8700 3600
Wire Wire Line
	4500 1700 4350 1700
Wire Wire Line
	4350 2250 4500 2250
Wire Wire Line
	4350 2250 4350 2600
Wire Wire Line
	4350 2850 4500 2850
Connection ~ 4350 2250
Wire Wire Line
	4350 2850 4350 3500
Wire Wire Line
	4350 3500 4500 3500
Connection ~ 4350 2850
Wire Wire Line
	4350 3500 4350 3750
Wire Wire Line
	4350 3750 4750 3750
Connection ~ 4350 3500
Wire Wire Line
	4100 4350 4750 4350
Wire Wire Line
	9550 1950 9450 1950
Wire Wire Line
	4350 1700 4350 2250
Text HLabel 1250 2500 0    50   Input ~ 0
CV1
Text HLabel 1250 2600 0    50   Input ~ 0
CV2
Text HLabel 1250 2700 0    50   Input ~ 0
CV3
Wire Wire Line
	3100 2750 4500 2750
Text HLabel 1250 2800 0    50   Input ~ 0
GATE
$Comp
L Device:R R?
U 1 1 5FE9EC1A
P 3950 4350
AR Path="/5FE9EC1A" Ref="R?"  Part="1" 
AR Path="/5FD0E1E1/5FE9EC1A" Ref="R?"  Part="1" 
AR Path="/5FE79040/5FE9EC1A" Ref="R2"  Part="1" 
F 0 "R2" H 4020 4396 50  0000 L CNN
F 1 "150" H 4020 4305 50  0000 L CNN
F 2 "" V 3880 4350 50  0001 C CNN
F 3 "~" H 3950 4350 50  0001 C CNN
	1    3950 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 4350 3550 4350
Wire Wire Line
	3550 4350 3550 3400
Connection ~ 3550 3400
Wire Wire Line
	3550 3400 4500 3400
NoConn ~ 4850 1150
$Comp
L Connector:Conn_01x06_Female J6
U 1 1 5FEBC6AE
P 6900 2500
F 0 "J6" H 6928 2476 50  0000 L CNN
F 1 "Panel Connector Female Bottom" H 6928 2385 50  0000 L CNN
F 2 "" H 6900 2500 50  0001 C CNN
F 3 "~" H 6900 2500 50  0001 C CNN
	1    6900 2500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J5
U 1 1 5FEBE565
P 1450 2500
F 0 "J5" H 1478 2476 50  0000 L CNN
F 1 "Panel Connector Female Top" H 1478 2385 50  0000 L CNN
F 2 "" H 1450 2500 50  0001 C CNN
F 3 "~" H 1450 2500 50  0001 C CNN
	1    1450 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 2300 2150 2300
Text HLabel 1250 2300 0    50   Input ~ 0
3.3V
Text HLabel 6700 2300 0    50   Input ~ 0
5V
Text HLabel 6700 2400 0    50   BiDi ~ 0
D-
Text HLabel 6700 2500 0    50   BiDi ~ 0
D+
Text HLabel 6700 2600 0    50   Input ~ 0
GND
Text HLabel 6700 2700 0    50   Input ~ 0
USBLED1
Text HLabel 6700 2800 0    50   Input ~ 0
USBLED2
Text HLabel 1250 2400 0    50   Output ~ 0
TOGGLE
Wire Wire Line
	4850 950  2150 950 
Wire Wire Line
	2150 950  2150 2300
$Comp
L Switch:SW_SPDT SW?
U 1 1 5FEA45AB
P 4650 1050
AR Path="/5FEA45AB" Ref="SW?"  Part="1" 
AR Path="/5FE79040/5FEA45AB" Ref="SW1"  Part="1" 
F 0 "SW1" H 4650 1335 50  0000 C CNN
F 1 "SW_SPDT" H 4650 1244 50  0000 C CNN
F 2 "" H 4650 1050 50  0001 C CNN
F 3 "~" H 4650 1050 50  0001 C CNN
	1    4650 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 2400 2250 2400
Wire Wire Line
	2250 2400 2250 1050
Wire Wire Line
	2250 1050 4450 1050
Wire Wire Line
	1250 2500 2350 2500
Wire Wire Line
	2350 2500 2350 1600
Wire Wire Line
	2350 1600 4500 1600
Wire Wire Line
	2450 2600 2450 2150
Wire Wire Line
	2450 2150 4500 2150
Wire Wire Line
	3100 2750 3100 2700
Wire Wire Line
	3100 2700 1250 2700
Wire Wire Line
	2650 3400 2650 2800
Wire Wire Line
	2650 2800 1250 2800
Wire Wire Line
	2650 3400 3550 3400
Wire Wire Line
	1250 2600 2450 2600
Wire Wire Line
	6700 2600 6150 2600
Connection ~ 4350 2600
Wire Wire Line
	4350 2600 4350 2850
Wire Wire Line
	9450 1950 6150 1950
Wire Wire Line
	6150 1950 6150 2600
Connection ~ 9450 1950
Connection ~ 6150 2600
Wire Wire Line
	6150 2600 4350 2600
Wire Wire Line
	6700 2400 7550 2400
Wire Wire Line
	7550 2400 7550 2250
Wire Wire Line
	7550 2250 9150 2250
Wire Wire Line
	7700 2500 7700 2350
Wire Wire Line
	7700 2350 9150 2350
Wire Wire Line
	7250 2300 7250 2550
Wire Wire Line
	7250 2550 9150 2550
Wire Wire Line
	9450 3000 8250 3000
Wire Wire Line
	8250 3000 8250 2700
Wire Wire Line
	8250 2700 6700 2700
Wire Wire Line
	8700 3600 8700 3100
Wire Wire Line
	8700 3100 8150 3100
Wire Wire Line
	8150 3100 8150 2800
Wire Wire Line
	8150 2800 6700 2800
Wire Wire Line
	6700 2500 7700 2500
Wire Wire Line
	6700 2300 7250 2300
$EndSCHEMATC
