<map version="freeplane 1.3.0">
<!--To view this file, download free mind mapping software Freeplane from http://freeplane.sourceforge.net -->
<node TEXT="Auslese-Simulation v2" ID="ID_1723255651" CREATED="1283093380553" MODIFIED="1491391171618"><hook NAME="MapStyle" zoom="1.087">

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node">
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right">
<stylenode LOCALIZED_TEXT="default" MAX_WIDTH="600" COLOR="#000000" STYLE="as_parent">
<font NAME="SansSerif" SIZE="10" BOLD="false" ITALIC="false"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.note"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important">
<icon BUILTIN="yes"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#0033ff">
<font SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#00b439">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#990000">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#111111">
<font SIZE="10"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="10"/>
<node TEXT="Detektor-Base" POSITION="left" ID="ID_1473787457" CREATED="1491391709010" MODIFIED="1491391726260">
<edge COLOR="#0000ff"/>
<node TEXT="Adresse" ID="ID_1384862688" CREATED="1491391728618" MODIFIED="1491391788281"/>
<node TEXT="Adress-Name" ID="ID_147111680" CREATED="1491391788963" MODIFIED="1491391796709">
<node TEXT="XML-Lader: Zuordnung zu Layer" ID="ID_404618983" CREATED="1491391798108" MODIFIED="1491391811955"/>
</node>
<node TEXT="ROC-Vektor" ID="ID_863622782" CREATED="1491391813045" MODIFIED="1491391838203"/>
<node TEXT="Position" ID="ID_683686978" CREATED="1491391855251" MODIFIED="1491391857521"/>
<node TEXT="Size" ID="ID_585714520" CREATED="1491391857799" MODIFIED="1491391859296"/>
<node TEXT="Gr&#xf6;&#xdf;e an Inhalt anpassen" ID="ID_1923666505" CREATED="1491391860212" MODIFIED="1491391881135"/>
</node>
<node TEXT="Detektor" POSITION="left" ID="ID_156541565" CREATED="1491391951790" MODIFIED="1491391954063">
<edge COLOR="#00ff00"/>
<node TEXT="Erbt von Detector-Base" ID="ID_753318485" CREATED="1491391955759" MODIFIED="1491391961924"/>
<node TEXT="implementiert StateMachine" ID="ID_639415964" CREATED="1491391962362" MODIFIED="1491391968884">
<node TEXT="currentState" ID="ID_1147431770" CREATED="1491391969900" MODIFIED="1491391974892"/>
<node TEXT="nextstate()" ID="ID_1311031117" CREATED="1491391975312" MODIFIED="1491391983957"/>
<node TEXT="enum States" ID="ID_444572410" CREATED="1491391984755" MODIFIED="1491391992203"/>
<node TEXT="clockUp()" ID="ID_1135465375" CREATED="1491391995558" MODIFIED="1491392204811">
<node TEXT="Aktivit&#xe4;ten der StateMachine" ID="ID_318046231" CREATED="1491392213404" MODIFIED="1491392225284"/>
</node>
<node TEXT="clockDown()" ID="ID_1327373321" CREATED="1491391999893" MODIFIED="1491392207022">
<node TEXT="Aktivit&#xe4;ten der StateMachine" ID="ID_101316245" CREATED="1491392228673" MODIFIED="1491392236426"/>
</node>
</node>
<node TEXT="reicht fstream-Pointer weiter zum Speichern der Hits" ID="ID_173026448" CREATED="1491396612824" MODIFIED="1491396625830"/>
</node>
<node TEXT="ReadoutCell-Base" POSITION="left" ID="ID_445708901" CREATED="1491392258203" MODIFIED="1491392603687">
<edge COLOR="#ff00ff"/>
<node TEXT="Adresse" ID="ID_729911448" CREATED="1491392290538" MODIFIED="1491392295308"/>
<node TEXT="Adress-Name" ID="ID_1779076710" CREATED="1491392295632" MODIFIED="1491392300298"/>
<node TEXT="Buffer-Gr&#xf6;&#xdf;e" ID="ID_1947908023" CREATED="1491392301137" MODIFIED="1491392310235"/>
<node TEXT="Buffer" ID="ID_1470177423" CREATED="1491392311109" MODIFIED="1491392315360">
<node TEXT="Queue? oder besser Vector wegen prio-Logik?" ID="ID_893857146" CREATED="1491392316746" MODIFIED="1491392555436">
<icon BUILTIN="help"/>
</node>
</node>
<node TEXT="ROC-Vektor" ID="ID_341632539" CREATED="1491392570832" MODIFIED="1491392576832"/>
<node TEXT="Pixel-Vektor" ID="ID_1959737148" CREATED="1491392577242" MODIFIED="1491392581271"/>
<node TEXT="Auslese-Funktionen" ID="ID_618344526" CREATED="1491392947021" MODIFIED="1491392951192">
<node TEXT="LoadPixelFlag()" ID="ID_85144260" CREATED="1491392620635" MODIFIED="1491552472549">
<icon BUILTIN="stop-sign"/>
<node TEXT="&quot;Synchronisieren&quot; der Pixel-Hits" ID="ID_11330569" CREATED="1491392834429" MODIFIED="1491392862759"/>
<node TEXT="rekursiver Aufruf auf Detektor-ROC-Vektor" ID="ID_172571566" CREATED="1491392864641" MODIFIED="1491392884268"/>
<node TEXT="wird nicht mehr ben&#xf6;tigt, weil der Pixel nicht mehr selbst speichern kann" ID="ID_291804217" CREATED="1491552475902" MODIFIED="1491552498672"/>
</node>
<node TEXT="LoadPixel()" ID="ID_625645888" CREATED="1491392629402" MODIFIED="1491392635505">
<node TEXT="Auslesen von Pixeln in allen ROCs" ID="ID_185075400" CREATED="1491392819492" MODIFIED="1491392832348"/>
<node TEXT="rekursiver Aufruf auf Detektor-ROC-Vektor" ID="ID_877938424" CREATED="1491392864641" MODIFIED="1491392884268"/>
</node>
<node TEXT="LoadROC(Adress-Name)" ID="ID_250563642" CREATED="1491392637254" MODIFIED="1491392649501">
<node TEXT="liest nur aus ROCs mit passendem Adress-Name die Hits aus den n&#xe4;chst-unteren ROCs aus" ID="ID_52540243" CREATED="1491392759246" MODIFIED="1491392789521"/>
<node TEXT="keine Pixel-Auslese" ID="ID_496184630" CREATED="1491392800492" MODIFIED="1491392804763"/>
<node TEXT="rekursiver Aufruf auf Detektor-ROC-Vektor" ID="ID_923265161" CREATED="1491392864641" MODIFIED="1491392884268"/>
</node>
<node TEXT="ReadROC()" ID="ID_1634593479" CREATED="1491392663095" MODIFIED="1491392696739">
<node TEXT="Auslesen der obersten ROC durch den Detektor" ID="ID_1141420230" CREATED="1491392698167" MODIFIED="1491392755578"/>
<node TEXT="Aufruf nur auf Detektor-ROC-Vektor, keine Kind-ROCs" ID="ID_1799791793" CREATED="1491392908135" MODIFIED="1491392933145"/>
</node>
</node>
<node TEXT="ShiftROC()" ID="ID_58447973" CREATED="1491393219912" MODIFIED="1491393240575">
<node TEXT="verschiebt alle Elemente um &#xfc;bergebenen Vektor" ID="ID_86412184" CREATED="1491393241815" MODIFIED="1491393260356"/>
<node TEXT="f&#xfc;r XML-Lader (LoadNPixels())" ID="ID_383395986" CREATED="1491393260715" MODIFIED="1491393280693"/>
</node>
</node>
<node TEXT="ReadoutCell-Arten" POSITION="left" ID="ID_977312576" CREATED="1491393125796" MODIFIED="1491393131002">
<edge COLOR="#00ffff"/>
<node TEXT="Unterscheidungskriterien" ID="ID_1884104775" CREATED="1491393450059" MODIFIED="1491393456615">
<node TEXT="Column-Drain oder PPtB" ID="ID_1305590031" CREATED="1491393457893" MODIFIED="1491393469609"/>
<node TEXT="&#xdc;berschreib-Mechanismus" ID="ID_1570786033" CREATED="1491393470085" MODIFIED="1491393687866">
<node TEXT="nicht lesen, wenn noch voll" ID="ID_192200233" CREATED="1491393688922" MODIFIED="1491393698845"/>
<node TEXT="lesen + L&#xf6;schen, aber nicht &#xfc;berschreiben" ID="ID_1409547183" CREATED="1491393699158" MODIFIED="1491393719703"/>
<node TEXT="Lesen, L&#xf6;schen und &#xdc;berschreiben" ID="ID_1983817320" CREATED="1491393720259" MODIFIED="1491393733520"/>
</node>
<node TEXT="Zero-Suppressed Output" ID="ID_123304581" CREATED="1491393764988" MODIFIED="1491393926412">
<node TEXT="normalerweise true, au&#xdf;er bei &quot;Schieberegistern&quot;" ID="ID_1678733584" CREATED="1491393927918" MODIFIED="1491393940413"/>
<node TEXT="ggf. Buffer-Gr&#xf6;&#xdf;e auf mindestens L&#xe4;nge des ROC-Vectors setzen&#xa;(f&#xfc;r Schieberegister)" ID="ID_1248494653" CREATED="1491394288079" MODIFIED="1491394342598"/>
</node>
<node TEXT="Auslese-Reihenfolge" ID="ID_501928508" CREATED="1491394028989" MODIFIED="1491394033976">
<node TEXT="FIFO" ID="ID_187976730" CREATED="1491394065595" MODIFIED="1491394068075">
<node TEXT="bzgl. Eintrag" ID="ID_67372747" CREATED="1491394116987" MODIFIED="1491394123604"/>
</node>
<node TEXT="First-Free-In-First-Position-Out" ID="ID_1715706965" CREATED="1491394068436" MODIFIED="1491394084463">
<node TEXT="bzgl. Speicherplatz" ID="ID_1821671812" CREATED="1491394108098" MODIFIED="1491394115486"/>
</node>
</node>
</node>
<node TEXT="Implementierungsm&#xf6;glichkeiten" ID="ID_262794874" CREATED="1491493983933" MODIFIED="1491493990182">
<node TEXT="ein riesiger Haufen an Klassen" ID="ID_1697085057" CREATED="1491493991157" MODIFIED="1491494012976">
<icon BUILTIN="button_cancel"/>
</node>
<node TEXT="eine ReadoutCell Klasse, die die wichtigen Funktionen aus untergeordneten Klassen bekommt" ID="ID_1548520148" CREATED="1491494014482" MODIFIED="1491494085085">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="auszulagernde Funktionen" ID="ID_1788095914" CREATED="1491494092270" MODIFIED="1491494104827">
<node TEXT="Buffer" ID="ID_514053652" CREATED="1491494105805" MODIFIED="1491494108883"/>
<node TEXT="Buffer-F&#xfc;llen" ID="ID_841244193" CREATED="1491494112578" MODIFIED="1491494119614">
<node TEXT="PPtB/Column-Drain" ID="ID_1592797675" CREATED="1491494148167" MODIFIED="1491494157180"/>
<node TEXT="&#xdc;berschreibmechanismus" ID="ID_1168934403" CREATED="1491494157446" MODIFIED="1491494165682"/>
<node TEXT="Zero-Suppression" ID="ID_156176004" CREATED="1491494185073" MODIFIED="1491494189060"/>
</node>
<node TEXT="Buffer-Auslese (Reihenfolge)" ID="ID_20734354" CREATED="1491494120017" MODIFIED="1491494133336"/>
</node>
</node>
<node TEXT="Simulator" POSITION="right" ID="ID_1322549647" CREATED="1491391175013" MODIFIED="1491391176867">
<edge COLOR="#ff0000"/>
<node TEXT="Detektor(en)" ID="ID_1242092294" CREATED="1491391179293" MODIFIED="1491391195666"/>
<node TEXT="EventGenerator" ID="ID_894070592" CREATED="1491391199096" MODIFIED="1491391202909">
<node TEXT="Referenz auf Detektor(en) in Simulator" ID="ID_1924797788" CREATED="1491391205097" MODIFIED="1491391219443"/>
<node TEXT="Ausgabe-Datei f&#xfc;r generierte Hits" ID="ID_545303498" CREATED="1491391299361" MODIFIED="1491391308756"/>
</node>
<node TEXT="Zeit-Kontrolle" ID="ID_690302524" CREATED="1491391222496" MODIFIED="1491391231337">
<node TEXT="Stopp-Zeit" ID="ID_606965634" CREATED="1491391340590" MODIFIED="1491391344255"/>
<node TEXT="Stopp bei n Zyklen nach letzter Event-Platzierung" ID="ID_1531122423" CREATED="1491391344746" MODIFIED="1491391369750"/>
<node TEXT="ClockUp()" ID="ID_1292572329" CREATED="1491391395217" MODIFIED="1491392188474">
<node TEXT="ruft clockUp() f&#xfc;r alle Detektoren auf" ID="ID_93958364" CREATED="1491392162920" MODIFIED="1491392200489"/>
</node>
<node TEXT="ClockDown()" ID="ID_486636630" CREATED="1491391400114" MODIFIED="1491392190777">
<node TEXT="ruft clockDown() f&#xfc;r alle Detektoren auf" ID="ID_901359826" CREATED="1491392162920" MODIFIED="1491392195049"/>
</node>
<node TEXT="Platzierung der Hits" ID="ID_217360020" CREATED="1491398783540" MODIFIED="1491398792654">
<node TEXT="Addition von gleichzeitigen Hits" ID="ID_1871107388" CREATED="1491398794148" MODIFIED="1491398866921"/>
<node TEXT="nach ClockDown()" ID="ID_313445913" CREATED="1491398880761" MODIFIED="1491398886394"/>
</node>
<node TEXT="Umrechnung zwischen Timestamp und realer Zeit" ID="ID_662986850" CREATED="1491399569280" MODIFIED="1491399583945">
<icon BUILTIN="yes"/>
<node TEXT="Betriebsfrequenz StateMachine" ID="ID_1679317553" CREATED="1491399617636" MODIFIED="1491399629785"/>
</node>
</node>
<node TEXT="XML-Lader" ID="ID_653198203" CREATED="1491391243107" MODIFIED="1491391247579">
<node TEXT="Input-Datei" ID="ID_1710933400" CREATED="1491391248508" MODIFIED="1491391252432"/>
<node TEXT="LoadDetektor" ID="ID_959683051" CREATED="1491391422740" MODIFIED="1491391426475"/>
<node TEXT="LoadTCoord" ID="ID_411338603" CREATED="1491391426920" MODIFIED="1491391432866"/>
<node TEXT="LoadEventGenerator" ID="ID_928406331" CREATED="1491391434086" MODIFIED="1491391437732"/>
<node TEXT="LoadROC" ID="ID_919935463" CREATED="1491391438172" MODIFIED="1491391442291"/>
<node TEXT="LoadPixel" ID="ID_1448098288" CREATED="1491391442636" MODIFIED="1491391444838"/>
<node TEXT="LoadNPixels" ID="ID_853285881" CREATED="1491391445283" MODIFIED="1491391448464">
<node TEXT="auch f&#xfc;r ROCs / ROC-Strukturen" ID="ID_889019945" CREATED="1491391449455" MODIFIED="1491391467695"/>
<node TEXT="vielleicht umbenennen?" ID="ID_984714754" CREATED="1491391468113" MODIFIED="1491391479603">
<icon BUILTIN="help"/>
</node>
</node>
<node TEXT="Map: Zuordnung ROC-Layer -- ROC-Adress-Name" ID="ID_854925798" CREATED="1491391649467" MODIFIED="1491391685940"/>
</node>
<node TEXT="Ausgabe-Datei-Name f&#xfc;r erfolgreich gelesene Hits" ID="ID_156850602" CREATED="1491391272755" MODIFIED="1491391295493"/>
<node TEXT="Ausgabe-Datei f&#xfc;r &quot;verlorene&quot; Hits" ID="ID_219871625" CREATED="1491391569139" MODIFIED="1491391581294"/>
</node>
<node TEXT="Pixel" POSITION="right" ID="ID_614702881" CREATED="1491395015364" MODIFIED="1491395017450">
<edge COLOR="#7c0000"/>
<node TEXT="Position" ID="ID_1747957479" CREATED="1491395021442" MODIFIED="1491395023628"/>
<node TEXT="Gr&#xf6;&#xdf;e" ID="ID_1486513179" CREATED="1491395023898" MODIFIED="1491395026498"/>
<node TEXT="Adresse" ID="ID_249197927" CREATED="1491395026954" MODIFIED="1491395029574"/>
<node TEXT="Adress-Name" ID="ID_929136258" CREATED="1491395029874" MODIFIED="1491395032909"/>
<node TEXT="Schwelle" ID="ID_819426485" CREATED="1491395033336" MODIFIED="1491395037160"/>
<node TEXT="Nachweiseffizienz" ID="ID_1396932319" CREATED="1491395037586" MODIFIED="1491395048998"/>
<node TEXT="Totzeit-Ende" ID="ID_1051281475" CREATED="1491395060079" MODIFIED="1491395082590">
<node TEXT="falls das Event vor Ende des Siganls ausgelesen wird" ID="ID_1022361889" CREATED="1491551727311" MODIFIED="1491553323432"/>
</node>
<node TEXT="Totzeit-Skalierung" ID="ID_754599370" CREATED="1491395179922" MODIFIED="1491395184762">
<node TEXT="Wert zum Nachschauen f&#xfc;r EventGenerator" ID="ID_1938619874" CREATED="1491395187497" MODIFIED="1491395195712"/>
</node>
<node TEXT="Detektions-Verz&#xf6;gerung" ID="ID_1902958332" CREATED="1491395200787" MODIFIED="1491395210586"/>
<node TEXT="kein HitFlag" ID="ID_204104320" CREATED="1491396190468" MODIFIED="1491396196040">
<node TEXT="daf&#xfc;r gibt es eine ROC mit nur diesem Pixel" ID="ID_979661762" CREATED="1491396196782" MODIFIED="1491396209601"/>
</node>
<node TEXT="Am Anfang von jedem Takt-Zyklus muss Hit gel&#xf6;scht werden k&#xf6;nnen" ID="ID_558056985" CREATED="1491396329656" MODIFIED="1491396415497"/>
<node TEXT="Hit-Speicher" ID="ID_861383476" CREATED="1491396425835" MODIFIED="1491396431318">
<node TEXT="wird am Ende der Totzeit gel&#xf6;scht" ID="ID_1843254539" CREATED="1491396634478" MODIFIED="1491396643024"/>
</node>
</node>
<node TEXT="Hit" POSITION="right" ID="ID_829787598" CREATED="1491396433801" MODIFIED="1491396435262">
<edge COLOR="#007c00"/>
<node TEXT="map: Adress-Name, Adresse" ID="ID_1337243065" CREATED="1491396436571" MODIFIED="1491396452078"/>
<node TEXT="map: Adress-Name, Auslese-Zeitpunkt" ID="ID_1785084314" CREATED="1491396452664" MODIFIED="1491396469576"/>
<node TEXT="double timestamp" ID="ID_458418310" CREATED="1491396470167" MODIFIED="1491396485648"/>
<node TEXT="double deadtimeend" ID="ID_1426264051" CREATED="1491396509122" MODIFIED="1491396517833"/>
<node TEXT="double Ladung" ID="ID_525394370" CREATED="1491398931246" MODIFIED="1491398937132">
<node TEXT="die diesen Hit erzeugt hat" ID="ID_1943079528" CREATED="1491399170555" MODIFIED="1491399178383"/>
</node>
<node TEXT="Event-Index" ID="ID_972743394" CREATED="1491396576124" MODIFIED="1491396583277"/>
</node>
<node TEXT="EventGenerator" POSITION="right" ID="ID_1880967852" CREATED="1491396668110" MODIFIED="1491396672080">
<edge COLOR="#7c007c"/>
<node TEXT="zuk&#xfc;nftig auch EventLoader" ID="ID_1533472351" CREATED="1491396687431" MODIFIED="1491396699165"/>
<node TEXT="Pointer auf Detektor(en) aus Simualtor" ID="ID_1529448610" CREATED="1491396700307" MODIFIED="1491396744558"/>
<node TEXT="Event-Index-Counter" ID="ID_500893877" CREATED="1491396744983" MODIFIED="1491396755788"/>
<node TEXT="Parameter" ID="ID_335502637" CREATED="1491396756278" MODIFIED="1491396785057">
<node TEXT="Event-Rate" ID="ID_1679061271" CREATED="1491396786180" MODIFIED="1491396789734"/>
<node TEXT="Cluster-Size" ID="ID_48438385" CREATED="1491396790160" MODIFIED="1491396792919"/>
<node TEXT="Random-Seed" ID="ID_863554287" CREATED="1491396793485" MODIFIED="1491396808654"/>
<node TEXT="Inclination-Sigma" ID="ID_1044038835" CREATED="1491396809795" MODIFIED="1491396813613"/>
<node TEXT="Charge-Scale" ID="ID_503462708" CREATED="1491396814784" MODIFIED="1491396817967"/>
<node TEXT="MinSize" ID="ID_392092533" CREATED="1491396818477" MODIFIED="1491396821206">
<node TEXT="minimum Size of Voxel for Calculation" ID="ID_414683703" CREATED="1491396832277" MODIFIED="1491396842391"/>
</node>
<node TEXT="Gaussian-Cut-Off" ID="ID_1771065263" CREATED="1491396821888" MODIFIED="1491396830751">
<node TEXT="e.g. number of sigmas" ID="ID_1087209451" CREATED="1491396844842" MODIFIED="1491396876475"/>
</node>
<node TEXT="Number of Events to Generate" ID="ID_590904494" CREATED="1491398467814" MODIFIED="1491398475945"/>
</node>
<node TEXT="Ausgabe-Datei f&#xfc;r generierte Events" ID="ID_1547064490" CREATED="1491396883923" MODIFIED="1491396894385"/>
<node TEXT="deque Hit-Liste" ID="ID_179860196" CREATED="1491396898296" MODIFIED="1491396922823"/>
<node TEXT="Start- und Endzeit-Berechnung" ID="ID_925604964" CREATED="1491398523143" MODIFIED="1491398534282">
<node TEXT="TimeWalk-Korrektur der Startzeit" ID="ID_1378350953" CREATED="1491398502416" MODIFIED="1491398522819"/>
<node TEXT="Verz&#xf6;gerung des Pixels" ID="ID_514985149" CREATED="1491398536977" MODIFIED="1491398546675"/>
<node TEXT="Totzeit" ID="ID_24964303" CREATED="1491398548531" MODIFIED="1491398559250">
<node TEXT="Ber&#xfc;cksichtige Totzeit-Skalierung im Pixel" ID="ID_1366154075" CREATED="1491398559889" MODIFIED="1491398585565"/>
</node>
</node>
</node>
</node>
</map>
