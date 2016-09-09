<?php
/**
 * Note:
 * This method requires the php.ini setting phar.readonly to be set to 0 in order to work for Phar objects. Otherwise, a PharException will be thrown.
 */
	try {
		$tarphar = new PharData('neo4jphp.zip');
		// convert it to the phar file format
		// note that myphar.tar is *not* unlinked
		$phar = $tarphar->convertToExecutable(Phar::PHAR); // creates myphar.phar
		$phar->setStub($phar->createDefaultStub('cli.php', 'web/index.php'));
		// creates myphar.phar.tgz
		$compressed = $tarphar->convertToExecutable(Phar::TAR, Phar::GZ, '.phar.tgz');
	} catch (Exception $e) {
		echo $e->getMessage();
	}
?>