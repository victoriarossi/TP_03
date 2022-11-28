# TP_03

# Alumnos 
Abril Occihipinti, 61159
Nicolas Suarez Durrels, 62468
Victoria Rossi, 61131

# Objetivo
Este trabajo consiste en buscar un sistema operativo de código abierto e investigar sus características.  

# Clonar el proyecto
	   git clone --recurse-submodules https://github.com/victoriarossi/TP_03.git


# Compilación 
	docker pull aocchipinti/so-tp3:1.0
	docker run -v "${PWD}:/root" --privileged -ti aocchipinti/so-tp3:1.0
	cd root
	make all

# Ejecución
    exit
	./runqemu.sh

# Documentación Oficial
	http://bluekernel.com.au/#intro,Summary,0,false
 
