<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <!-- FileName: position67 -->
  <!-- Document: http://www.w3.org/TR/xpath -->
  <!-- DocVersion: 19991116 -->
  <!-- Section: 2.4 -->
  <!-- Creator: David Marston -->
  <!-- Purpose: Test of number function to make positional indexing definite. -->

<xsl:template match="doc">
  <out>
    <xsl:value-of select="a[number('3')]"/>
  </out>
</xsl:template>

</xsl:stylesheet>
