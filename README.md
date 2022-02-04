# ROS_Workshop
Dieses Repository stellt einen kleinen Ros workshop dar.
Es gibt mehrere branches für die einzelen Aufgaben, dabei gibt es jeweils einen
unterordner "task" in dem die Aufgabenstellung beschreiben ist.

## Setup

### Clonen
<code>mkdir -p ~/workshop_ws/src</code>

<code>cd ~/workshop_ws/src</code>

<code>git clone (clone-link) prep_pkg</code>

### Initialisieren der Workspaces
<code>cd ~/workshop_ws/src/prep_pkg</code>

<code>git checkout Aufgabe{1, 2, 3}</code>

<code>cd ~/workshop_ws</code>

<code>catkin_make</code>

### Einrichten eines Packets zum Bearbeiten der Aufgaben

<code>cd ~/workshop_ws/src</code>

#### Nach folgendem Schema werden packages generiert: <br>
<code>catkin_create_pkg (packagename) [dependency1, dependency2, ...]</code>

#### Hier braucht ihr den command: <br>
<code>catkin_create_pkg (einen namen eurer wahl im snake_case) roscpp prep_pkg</code>
<br>
<br>
<br>
<code>cd ~/workshop_ws && catkin_make</code>

## ROS Projekte öffnen und Ausführen mit Clion

Damit Clion sämtliche ROS Abhängigkeiten auf euer Projekt findet, muss Clion vom Terminal aus gestartet werden. <br>
Zuvor muss aber die Environment vorbereitet werden. Dazu müsst ihr folgendes tun.

### Schritte, die jedes Mal beim Öffnen eines ROS Projektes getan werden müssen
<code>source ~/path/to/workspace/devel/setup.bash</code>

#### Also für den Workshop: <br>
<code>source ~/workshop_ws/devel/setup.bash</code>

#### Öffnen von Clion übers Terminal: <br>
<code>sh /path/to/clion/bin/clion.sh</code>

Falls ihr Clion per <code>snap</code> installiert habt, findet ihr das shell script unter folgendem Pfad: <br>
<code>/snap/clion/current/bin/clion.sh</code>

#### Öffnen des Projekts
<code>File>Open...></code> Im Dialogfenster dann folgenden Pfad auswählen: <br>
<code>/home/[user]/path/to/workspace/src/CMakeLists.txt</code> <b>UND DANN "OPEN AS PROJECT"</b>

### Schritte die einmal pro ROS Projekt gemacht werden müssen

Wenn ihr ein ROS Project das erste Mal in Clion öffnet, öffnet sich auch ein Dialogfenster, dass ihr auch unter<br>
<code>File>Setting>Code, Execution, Deployment>CMake</code><br>
findet.

#### Generator
Clion hat 2019 die Möglichkeit eingeführt andere Generatoren als UNIX MAKEFILE zu verwenden und hat den Generator<br>
"Ninja" in 2021 als Default eingestellt. Für sämtliche ROS Projekte müsst ihr allerdings "UNIX MAKEFILE" als Generator<br>
einstellen.<br>
Wenn ihr das nicht für jedes Projekt ändern wollt, könnt ihr unter <br>
<code>File>Setting>Advanced Settings>CMake | Use Legacy Generator for CMake 3.20 and higher</code><br>
den Haken setzten.<br>

#### CMake Options
Wenn in dem Feld schon etwas drin steht, ignoriert es einfach und fügt am Ende folgendes hinzu: <br>
<code>-DCATKIN_DEVEL_PREFIX:PATH=/home/[user]/path/to/workspace/devel</code><br>
Für den Workshop also:<br>
<code>_DCATKIN_DEVEL_PREFIX:PATH=/home/[user]/workshop_ws/devel</code>

#### Build Directory
Hier muss einfach nur der Build Ordner angegeben werden:<br>
<code>/home/[user]/path/to/workspace/build<code><br>
Für den Workshop also:<br>
<code>/home/[user]/workshop_ws/build</code>