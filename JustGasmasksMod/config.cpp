class CfgPatches
{
	class JustGasmasks
	{
		requiredAddons[]=
		{
			"DZ_Scripts"
		};
		author="GoonWolf";
	};
};
class CfgMods
{
	class JustGasmasks
	{
		type = "mod";
		dependencies[]={};	
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = 
				{
					"JustGasmasksMod/WorldScripts"
				};
			};
		};
	};
};