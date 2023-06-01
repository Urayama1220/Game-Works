<?xml version="1.0" encoding="UTF-8"?>
<moduleList name = "Player" version = "1.0">
	<actNode name = "MoveLR">
				<module name = "TitleCheckObjR" w = "10" speed = "6" Checkcenterx = "6" Checkcentery = "24">
						<module  name = "Move" x = "6"/>
						<module name = "CheckState" state = "Uprun">
							<module name = "SetAnime" state = "run"/>
						</module>
				</module>
	</actNode>
	<actNode name = "ReMove">
		<module name = "Checkflag" flag = "true">
			<module name = "SetAnime" state = "Uprun"/>
		</module>
	</actNode>
</moduleList>