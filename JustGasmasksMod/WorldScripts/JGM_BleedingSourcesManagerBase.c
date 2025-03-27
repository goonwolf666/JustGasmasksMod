modded class BleedingSourcesManagerBase
{	
	override bool AttemptAddBleedingSourceDirectly(int bit, eBleedingSourceType type = eBleedingSourceType.NORMAL, int context = 0)
	{		
		if(CanAddBleedingSource(bit))
		{
			// Check gas mask
			if (m_Player.FindAttachmentBySlotName("Mask"))
			{
				Clothing maskClothes = Clothing.Cast(m_Player.FindAttachmentBySlotName("Mask"));
				if (maskClothes && maskClothes.IsGasMask())
				{
					MaskBase mask = MaskBase.Cast(maskClothes);	
					if(mask.HasValidFilter() && !type == eBleedingSourceType.NORMAL)
					{
						//Print("AttemptAddBleedingSourceDirectly - found MASK and type:" + type + ", skipping bleed"); //DEBUG
						return false;
					}
				}
			}
	
		AddBleedingSourceEx(bit, type, context);
		return true;
		}
		
	return false;
	}
}