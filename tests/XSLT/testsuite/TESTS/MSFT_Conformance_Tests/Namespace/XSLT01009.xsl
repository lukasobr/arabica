<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="null">
  <xsl:template match="bookstore/book">
    
          
          <xsl:apply-templates select="author"/>

           

          

		

 </xsl:template>

 <xsl:template match="author" priority="">
- <SPAN style="color=green" ID="test">
  <xsl:value-of select="my:country" /> 
  </SPAN>
  </xsl:template>

 

 <xsl:template match="author" priority="-.5">
- <SPAN style="color=red" ID="test">
  <xsl:value-of select="my:country" /> 
  </SPAN>
  </xsl:template>


	


</xsl:stylesheet>
