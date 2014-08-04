<?php

/**
 * @file
 * Template for Back to Parent link.
 * Variables:
 *   $btp_link_item
 *     contains the parent menu item array, and block config settings.
 *   $btp_prefix
 *     contains the prefix string.
 *   $btp_suffix
 *     contains the suffix string.
 */

?>
<?php if (isset($ftc_link_item)) : ?>
<div class="ftc-link">
  <?php print l($ftc_link_item['ftc_prefix'] . $ftc_link_item['link_title'] . $ftc_link_item['ftc_suffix'], $ftc_link_item['link_path'], $ftc_link_item['localized_options']);?>
</div>
<?php endif; ?>
