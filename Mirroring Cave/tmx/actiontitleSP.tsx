<?xml version="1.0" encoding="UTF-8"?>
<moduleList name = "Player" version = "1.0">
	<actNode name = "MoveLR">
				<module name = "TitleCheckObjRSP" w = "10" speed = "6" Checkcenterx = "6" Checkcentery = "24">
						<module  name = "MoveSP" x = "6"/>
						<module name = "CheckStateSP" state = "Uprun">
							<module name = "SetAnimeSP" state = "run"/>
						</module>
				</module>
	</actNode>
	<actNode name = "ReMove">
		<module name = "CheckflagSP" flag = "true">
			<module name = "SetAnimeSP" state = "Uprun"/>
		</module>
	</actNode>
</moduleList>