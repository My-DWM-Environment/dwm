static void
tile2(Monitor *m)
{
	unsigned int i, n, h, mw, my, ty;
	float tagmfact;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
		;
	if (n == 0)
		return;

	if (n > m->nmaster) {
		for (int j = 0; j < LENGTH(tags); j++)
			if (((1 << j) & TAGMASK) == m->tagset[m->seltags]) {
				tagmfact = tags[j].mfact;
				break;
			}
			if (!tagmfact)
				tagmfact = m->mfact;
		mw = m->nmaster ? m->ww * tagmfact : 0;
	} else
		mw = m->ww;
	for (i = my = ty = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster)
		{
			h = (m->wh - my) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx, m->wy + my, mw - (2 * c->bw), h - (2 * c->bw), 0);
			my += HEIGHT(c);
		}
		else
		{
			if (i == 1)
				h = ((m->wh - ty) / (n - i)) + 350;
			if (i == 2)
				h = (m->wh - ty) / (n - i);
			resize(c, m->wx + mw, m->wy + ty, m->ww - mw - (2 * c->bw), h - (2 * c->bw), 0);
			ty += HEIGHT(c);
		}
}